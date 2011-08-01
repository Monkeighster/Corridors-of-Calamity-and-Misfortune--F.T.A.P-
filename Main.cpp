#include "Main.h"
#include "LevelGenerator.h"
#include "Character.h"
#include <iostream>

#define VIEW_WIDTH 70
#define VIEW_HEIGHT 20

using namespace std;

int main(int argc, char * argv[])
{
	char drawArray[VIEW_WIDTH * VIEW_HEIGHT];
	Level currentLevel = LevelGen::generateLevel(VIEW_WIDTH, VIEW_HEIGHT, 0);

	currentLevel.drawASCIIArray((char *)drawArray);

	for(int i = 0; i < VIEW_HEIGHT; i++)
	{
		for(int j = 0; j < VIEW_WIDTH; j++)
		{
			cout << currentLevel.getTile(j, i)->getASCIIchar();
		}
		cout << endl;
	}

	char endChar;
	cout << "Enter any key to quit." << endl << "> " << endl;
	cin >> endChar;

	return 0;
};