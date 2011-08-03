#include "Main.h"
#include "LevelGenerator.h"
#include "Character.h"
#include "Win32ConsoleIO.h"
#include <iostream>

#define VIEW_WIDTH 60
#define VIEW_HEIGHT 20

using namespace std;

int main(int argc, char * argv[])
{
	Win32ConsoleIO consoleIO = Win32ConsoleIO(VIEW_WIDTH, VIEW_HEIGHT);

	// Generate the level, and add a character to the level
	Level currentLevel = LevelGen::generateLevel(VIEW_WIDTH, VIEW_HEIGHT, 0);
	Player playerChar = Player(100);
	currentLevel.setPlayerCharacter(&playerChar, 3, 4);
	bool quitFlag = false;

	while(!quitFlag) {
		// Render the current game state
		consoleIO.drawLevel(&currentLevel);

		// Get updates from the user
		int keyVal = consoleIO.getNextKeypress();
		Tile * moveTile = NULL;
		switch(keyVal) {
		case KEY_ESCAPE:
			quitFlag = true;
			break;
		case KEY_UP_ARROW:
			moveTile = currentLevel.getTile(
				playerChar.getPosition()->xPosition(),
				playerChar.getPosition()->yPosition() - 1);
			break;
		case KEY_LEFT_ARROW:
			moveTile = currentLevel.getTile(
				playerChar.getPosition()->xPosition() - 1,
				playerChar.getPosition()->yPosition());
			break;
		case KEY_RIGHT_ARROW:
			moveTile = currentLevel.getTile(
				playerChar.getPosition()->xPosition() + 1,
				playerChar.getPosition()->yPosition());
			break;
		case KEY_DOWN_ARROW:
			moveTile = currentLevel.getTile(
				playerChar.getPosition()->xPosition(),
				playerChar.getPosition()->yPosition() + 1);
			break;
		}

		if(moveTile != NULL && moveTile->passable()) {
			playerChar.setPosition(moveTile);
		}
	}

	char endChar;
	cout << "Enter any key to quit." << endl << "> " << endl;
	cin >> endChar;

	return 0;
};