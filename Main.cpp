#include "Main.h"
#include "LevelGenerator.h"
#include "Character.h"
#include "ConsoleInput.h"
#include <iostream>

#define VIEW_WIDTH 70
#define VIEW_HEIGHT 20

using namespace std;

int main(int argc, char * argv[])
{
	char rowBuffer[VIEW_HEIGHT][VIEW_WIDTH + 1];
	for(int i = 0; i < VIEW_HEIGHT; i++) {
		rowBuffer[i][VIEW_WIDTH] = 0;	// Null terminate the string for each row
	}

	// Generate the level, and add a character to the level
	char drawArray[VIEW_WIDTH * VIEW_HEIGHT];
	Level currentLevel = LevelGen::generateLevel(VIEW_WIDTH, VIEW_HEIGHT, 0);
	Player playerChar = Player(100);
	currentLevel.setPlayerCharacter(&playerChar, 3, 4);
	bool quitFlag = false;

	while(!quitFlag) {
		// Render the current game state
		currentLevel.drawASCIIArray((char *)drawArray);
		system("cls");
		for(int i = 0; i < VIEW_HEIGHT; i++)
		{
			for(int j = 0; j < VIEW_WIDTH; j++)
			{
				Tile * curTile = currentLevel.getTile(j, i);
				// TODO: Just placeholder code for drawing the player character,
				// selection of the character should be handled in the Player class
				if(playerChar.getPosition() == curTile) {
					rowBuffer[i][j] = '@';
				} else {
					rowBuffer[i][j] = curTile->getASCIIchar();
				}
			}
		}
		for(int i = 0; i < VIEW_HEIGHT; i++) {
			cout << rowBuffer[i] << endl;
		}

		// Get updates from the user
		int keyVal = getNextKeypress();
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