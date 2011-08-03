#ifndef WIN32_CONSOLE_INPUT_H
#define WIN32_CONSOLE_INPUT_H

#include "LevelGenerator.h"
#include <Windows.h>
#include <conio.h>
#include <vector>

/** Platform specific key constants */
const static int ARROW_CONSTANT = 224;
const static int KEY_ESCAPE = 251;
const static int KEY_LEFT_ARROW = ARROW_CONSTANT + 75;
const static int KEY_RIGHT_ARROW = ARROW_CONSTANT + 77;
const static int KEY_UP_ARROW = ARROW_CONSTANT + 72;
const static int KEY_DOWN_ARROW = ARROW_CONSTANT + 80;

/** Platform specific color constants */
const static int COLOR_BLACK = 0;
const static int COLOR_BLUE = 1;
const static int COLOR_GREEN = 2;
const static int COLOR_RED = 4;
const static int COLOR_LIGHT_RED = 12;
const static int COLOR_YELLOW = 14;
const static int COLOR_WHITE = 15;

class Win32ConsoleChar {
private:
	int foregroundColor;
	int backgroundColor;
	char character;
public:
	Win32ConsoleChar(char character, int foregroundColor, int backgroundColor);

	/** Default Constructor (defaults to white foreground, black background) */
	Win32ConsoleChar(char character);

	void setCharacter(char character);
	void setForegroundColor(int foreground);
	void setBackgroundColor(int background);

	char getCharacter() const;

	int getColorCode() const;
};

class Win32ConsoleIO {
private:
	HANDLE stdOutHandle;

	int width;
	int height;

	std::vector<std::vector<Win32ConsoleChar>> consoleChars;
	std::vector<std::vector<bool>> changedFlags;
public:
	Win32ConsoleIO(int consoleWidth, int consoleHeight);

	/** Blocks until a keypress occurs, and returns the pressed key */
	int getNextKeypress();

	Win32ConsoleChar * getCharacter(int xPos, int yPos);

	/** Draws the passed level to the console */
	void drawLevel(Level * gameLevel);
};

#endif