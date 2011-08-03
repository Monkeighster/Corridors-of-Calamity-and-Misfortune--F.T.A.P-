#ifndef LEVEL_GEN_H
#define LEVEL_GEN_H

#include "Character.h"
#include <vector>

class Tile
{
private:
	bool isPassable;

	bool isDoor;

	/** X (width) and Y (height) position of the tile in its level */
	int xPos;
	int yPos;

public:
	Tile();
	
	Tile(bool isPassable, bool isDoor);

	void setPosition(int xPos, int yPos);

	int xPosition();

	int yPosition();

	char getASCIIchar();

	void setPassable(bool passable);

	bool passable();
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

	Player * getPlayer();

	int getWidth();

	int getHeight();

	/** Adds a player character to the level at the specified
	 * X and Y position */
	void setPlayerCharacter(Player * player, int xPos, int yPos);
};


class LevelGen
{
private:

public:
	static Level generateLevel(int width, int height, int numOfMonsters);	
};

#endif