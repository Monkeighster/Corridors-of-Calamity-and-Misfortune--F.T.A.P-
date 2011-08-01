#include "Main.h"
#include "LevelGenerator.h"
#include "Character.h"
#include <iostream> 

using namespace std;

int main(int argc, char * argv[])
{
	char drawArray[40 * 30];
	Level currentLevel = LevelGen::generateLevel(40, 30, 0);

	currentLevel.drawASCIIArray((char *)drawArray);

	for(int i = 0; i < 30; i++)
	{
		for(int j = 0; j < 40; j++)
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