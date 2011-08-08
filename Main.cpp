#include "Main.h"
#include "LevelGenerator.h"
#include "Character.h"
#include "Win32ConsoleIO.h"
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <conio.h>

#define VIEW_WIDTH 60
#define VIEW_HEIGHT 20

using namespace std;

int main(int argc, char * argv[])
{
	srand(time(NULL)); // Seed the random number generator

	Win32ConsoleIO consoleIO = Win32ConsoleIO(VIEW_WIDTH, VIEW_HEIGHT);

	// Generate the level, and add a character to the level
	Level currentLevel = LevelGen::generateLevel(VIEW_WIDTH, VIEW_HEIGHT, 0);
	Player playerChar = Player(100);

	// Find a passable tile to drop the player on
	int tileX, tileY;
	while(true) {
		tileX = (rand() % (VIEW_WIDTH)) + 1;
		tileY = (rand() % (VIEW_HEIGHT)) + 1;
		if(currentLevel.getTile(tileX, tileY) != NULL
			&&	currentLevel.getTile(tileX, tileY)->passable() == true) 
		{
			break;
		}
	}
	currentLevel.setPlayerCharacter(&playerChar, tileX, tileY);
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
		case KEY_R:
			currentLevel = LevelGen::generateLevel(VIEW_WIDTH, VIEW_HEIGHT, 0);
			// TODO: This section is just copypasta'd from above for testing purposes,
			// should be refactored
			// ------------------------------
			int tileX, tileY;
			while(true) {
				tileX = (rand() % (VIEW_WIDTH)) + 1;
				tileY = (rand() % (VIEW_HEIGHT)) + 1;
				if(currentLevel.getTile(tileX, tileY) != NULL
					&&	currentLevel.getTile(tileX, tileY)->passable() == true) 
				{
					break;
				}
			}
			currentLevel.setPlayerCharacter(&playerChar, tileX, tileY);
			consoleIO.forceFullRedraw();
			// ------------------------------

			break;
		}

		if(moveTile != NULL) {
			if(moveTile->door() && !moveTile->passable()) {
				moveTile->setPassable(true);
			} else if (moveTile->passable()) {
				playerChar.setPosition(moveTile);
			}
		}
	}
	
	return 0;
};