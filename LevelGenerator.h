#ifndef LEVEL_GEN_H
#define LEVEL_GEN_H

#include "Character.h"
#include <vector>

class Tile
{
private:
	bool isPassable;

	bool isDoor;

public:
	Tile();
	
	Tile(bool isPassable, bool isDoor);

	char getASCIIchar();

	void setPassable(bool passable);
};


class Level
{
private:
	int width;
	int height;
	Player * player;
	std::vector<std::vector<Tile>> tiles;

public:
	Level(int width, int height);
	
	~Level();	

	Tile  * getTile(int width,int height);

	void drawASCIIArray(char * arrayStart); 
};


class LevelGen
{
private:

public:
	static Level generateLevel(int width, int height, int numOfMonsters);	
};

#endif