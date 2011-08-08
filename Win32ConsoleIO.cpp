#include "Win32ConsoleIO.h"

// ----------------- Win32ConsoleChar Implementation ----------------- 

Win32ConsoleChar::Win32ConsoleChar(char character, int foregroundColor, int backgroundColor) :
	foregroundColor(foregroundColor), backgroundColor(backgroundColor), character(character)
{
}

Win32ConsoleChar::Win32ConsoleChar(char character) :
	foregroundColor(COLOR_WHITE), backgroundColor(COLOR_BLACK), character(character)
{
}

void Win32ConsoleChar::setCharacter(char character) {
	this->character = character;
}

void Win32ConsoleChar::setForegroundColor(int foreground)
{
	this->foregroundColor = foreground;
}

void Win32ConsoleChar::setBackgroundColor(int background)
{
	this->backgroundColor = background;
}

char Win32ConsoleChar::getCharacter() const
{
	return this->character;
}

int Win32ConsoleChar::getColorCode() const
{
	return this->foregroundColor + (16 * this->backgroundColor);
}


// ----------------- Win32ConsoleIO Implementation ----------------- 

Win32ConsoleIO::Win32ConsoleIO(int consoleWidth, int consoleHeight) :
		stdOutHandle((HANDLE)GetStdHandle(STD_OUTPUT_HANDLE)), width(consoleWidth),
		height(consoleHeight), consoleChars(), changedFlags()
{
	for(int i = 0; i < height; i++) {
		consoleChars.push_back(std::vector<Win32ConsoleChar>());
		changedFlags.push_back(std::vector<bool>());
		std::vector<Win32ConsoleChar> & charRow = consoleChars.back();
		std::vector<bool> & flagRow = changedFlags.back();
		for(int j = 0; j < width; j++) {
			charRow.push_back(Win32ConsoleChar('X'));
			flagRow.push_back(true);
		}
	}
}

int Win32ConsoleIO::getNextKeypress() 
{
	int keyVal = getch();
	if(keyVal == ARROW_CONSTANT) {
		keyVal = keyVal + getch();
	}
	return keyVal;
}

void Win32ConsoleIO::drawLevel(Level * gameLevel) {
	// Update the internal character array
	for(int i = 0; i < gameLevel->getWidth(); i++) {
		for(int j = 0; j < gameLevel->getHeight(); j++) {
			Tile * curTile = gameLevel->getTile(i, j);
			if(curTile->getASCIIchar() != consoleChars[j][i].getCharacter()
					|| changedFlags[j][i] == true)	// Always process changed consoleChars to deal with initialization
			{
				consoleChars[j][i].setCharacter(curTile->getASCIIchar());

				// Note: Colors and consoleChars should be read from a config file 
				// based on the tile type and contents 
				// (just hardcode it for pretty output for now)
				consoleChars[j][i].setForegroundColor(COLOR_WHITE);
				if(curTile->door() && !curTile->passable()) {
					consoleChars[j][i].setForegroundColor(COLOR_GREY);
					consoleChars[j][i].setBackgroundColor(COLOR_BROWN);
				} else if(curTile->passable()) {
					consoleChars[j][i].setForegroundColor(COLOR_WHITE);
					consoleChars[j][i].setBackgroundColor(COLOR_BLACK);
				} else {
					consoleChars[j][i].setForegroundColor(COLOR_BLACK);
					consoleChars[j][i].setBackgroundColor(COLOR_RED);
				}
				changedFlags[j][i] = true;
			}
		}
	}

	int playerXPos = gameLevel->getPlayer()->getPosition()->xPosition();
	int playerYPos = gameLevel->getPlayer()->getPosition()->yPosition();

	// Note: Colors and consoleChars should be read from a config file 
	// based on the character type (as above)
	consoleChars[playerYPos][playerXPos].setCharacter('@');
	consoleChars[playerYPos][playerXPos].setForegroundColor(COLOR_WHITE);
	consoleChars[playerYPos][playerXPos].setBackgroundColor(COLOR_BLUE);
	changedFlags[playerYPos][playerXPos] = true;

	// Write out any changed consoleChars to the screen
	COORD cursorPos;
	char writeChar[2];
	writeChar[1] = 0;
	DWORD nWritten; // Characters written
	for(int i = 0; i < gameLevel->getWidth(); i++) {
		for(int j = 0; j < gameLevel->getHeight(); j++) {
			if(changedFlags[j][i] == true) {
				changedFlags[j][i] = false;
				cursorPos.X = i;
				cursorPos.Y = j;
				writeChar[0] = consoleChars[j][i].getCharacter();
				SetConsoleCursorPosition(stdOutHandle, cursorPos);
				SetConsoleTextAttribute(stdOutHandle, consoleChars[j][i].getColorCode());
				DWORD nWritten; // Characters written
				WriteConsole(stdOutHandle, writeChar, 1, &nWritten, NULL );
			}
		}
	}
}

void Win32ConsoleIO::forceFullRedraw() {
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			changedFlags[j][i] = true;
		}
	}
}