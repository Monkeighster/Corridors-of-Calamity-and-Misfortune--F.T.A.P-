#ifndef LEVEL_GEN_H
#define LEVEL_GEN_H

#include "Character.h"
#include <vector>

const static int DIR_NORTH = 0;
const static int DIR_EAST = 1;
const static int DIR_SOUTH = 2;
const static int DIR_WEST = 3;

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

	int xPosition() const;

	int yPosition() const;

	char getASCIIchar() const;

	void setPassable(bool passable);

	void setDoor(bool door);

	bool passable() const;

	bool door() const;
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

	Tile  * getTile(int width, int height);

	Player * getPlayer() const;

	int getWidth() const;

	int getHeight() const;

	/** Adds a player character to the level at the specified
	 * X and Y position */
	void setPlayerCharacter(Player * player, int xPos, int yPos);

	void randomizeLevel(int minRoomSize, int roomVariance);

	/**
	 * @return True if the rectangle of the level starting at the specified
	 * top left corner with the specified width or height is composed entirely
	 * of impassable tiles.
	 */
	bool isRectEmpty(int cornerX, int cornerY, int width, int height);
};


class LevelGen
{
private:

public:
	static Level generateLevel(int width, int height, int numOfMonsters);	
};

#endif