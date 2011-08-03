#include "LevelGenerator.h"
#include <cstdlib>

// ----------------- Level Implementation -----------------

Level::Level(int width, int height): width(width), height(height), 
	player(NULL), tiles()
{
	for(int i = 0; i < height; i++) {
		tiles.push_back(std::vector<Tile>());
		std::vector<Tile> & rowVector = tiles.back();
		for(int j = 0; j < width; j++) {
			Tile newTile = Tile();
			newTile.setPosition(j, i);
			rowVector.push_back(newTile);
		}
	}

	for(int i = 2; i < 5; i++) {
		for(int j = 2; j < 8; j++) {
			this->getTile(i, j)->setPassable(true);
		}
	}

	this->getTile(5, 6)->setPassable(true);
	this->getTile(6, 6)->setPassable(true);
	this->getTile(7, 6)->setPassable(true);
	this->getTile(8, 6)->setPassable(true);

	for(int i = 9; i < 16; i++) {
		for(int j = 2; j < 15; j++) {
			this->getTile(i, j)->setPassable(true);
		}
	}
}

Level::~Level()
{
}

Tile * Level::getTile(int width, int height)
{
	if(width < 0 || width >= this->width ||
		height < 0 || height >= this->height) 
	{
		return NULL;
	}
	return &(tiles[height])[width];
}

Player * Level::getPlayer() {
	return this->player;
}

void Level::setPlayerCharacter(Player * player, int xPos, int yPos) {
	this->player = player;
	player->setPosition(getTile(xPos, yPos));
}

void Level::drawASCIIArray(char * arrayStart) {
	for(int i = 0; i < this->height; i++) {
		for(int j = 0; j < this->width; j++) {
			arrayStart[(i * this->width) + j] =
					getTile(j, i)->getASCIIchar();
		}
	}
}


// ----------------- Tile Implementation ----------------- 

Tile::Tile(): isPassable(false), isDoor(false), xPos(0), yPos(0)
{
}

Tile::Tile(bool isPassable, bool isDoor): isPassable(isPassable), isDoor(isDoor), 
	xPos(0), yPos(0)
{
}

void Tile::setPassable(bool passable)
{
	isPassable = passable;
}

void Tile::setPosition(int xPos, int yPos)
{
	this->xPos = xPos;
	this->yPos = yPos;
}

int Tile::xPosition()
{
	return xPos;
}

int Tile::yPosition()
{
	return yPos;
}

char Tile::getASCIIchar()
{
	if(!isPassable && !isDoor) 
	{
		return 'X';
	} 
	else if(isPassable && isDoor) 
	{
		return 'H';
	} 
	else if(isPassable && !isDoor) 
	{
		return '.';
	} 
	else if(!isPassable && isDoor) 
	{
		return 'D';
	}
}

bool Tile::passable() {
	return this->isPassable;
}


// ----------------- LevelGen Implementation ----------------- 

Level LevelGen::generateLevel(int width, int height, int numOfMonsters)
{
	Level newLevel = Level(width, height);
	return newLevel;
}