#include "LevelGenerator.h"
#include <cstdlib>

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

void Tile::setDoor(bool door)
{
	isDoor = door;
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
		return '#';
	} 
	else if(isPassable && isDoor) 
	{
		return 'O';
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

bool Tile::door() {
	return this->isDoor;
}


// ----------------- Level Implementation -----------------

Level::Level(int width, int height): width(width), height(height), 
	player(NULL), tiles()
{
	// Add all the tiles to the level, defaulting to impassable tiles
	for(int i = 0; i < height; i++) {
		tiles.push_back(std::vector<Tile>());
		std::vector<Tile> & rowVector = tiles.back();
		for(int j = 0; j < width; j++) {
			Tile newTile = Tile();
			newTile.setPosition(j, i);
			rowVector.push_back(newTile);
		}
	}

	int freeTiles = width * height;

	randomizeLevel(3 + (rand() % 3), 4 + (rand() % 4));
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

int Level::getWidth() {
	return this->width;
}

int Level::getHeight() {
	return this->height;
}

void Level::setPlayerCharacter(Player * player, int xPos, int yPos) {
	this->player = player;
	player->setPosition(getTile(xPos, yPos));
}

void Level::randomizeLevel(int minRoomSize, int roomVariance) {
	int freeTiles = height * width;
	
	// Generate a random room
	int roomWidth = (rand() % roomVariance) + minRoomSize;
	int roomHeight = (rand() % roomVariance) + minRoomSize;
	int cornerX = (rand() % ((width - 3) - roomWidth)) + 1;
	int cornerY = (rand() % ((height - 3) - roomHeight)) + 1;

	// Generate the first room
	for(int i = cornerX; i < cornerX + roomWidth - 1; i++) {
		for(int j = cornerY; j < cornerY + roomHeight - 1; j++) {
			this->getTile(i, j)->setPassable(true);
		}
	}
	freeTiles -= roomWidth * roomHeight;
	
	// Generate more rooms branching off until all freeTiles are used up (kind of...
	// the amount subtracted from freeTiles includes the room's walls, so some
	// overlap between rooms will occur. Practically, this means freeTiles is very
	// likely to drop under 0 before the level is actually full)
	int generatedRooms = 0;
	int failedAttempts = 0; // Keep a counter of failed attempts and abort if it gets too high
	while(freeTiles > 0
		&& failedAttempts < 200) 
	{
		int numNeighbouringPassable = 0;
		int randX = rand() % width;
		int randY = rand() % height;
		int generateDir;

		if(getTile(randX, randY)->passable()) {
			failedAttempts++;
			continue;
		}

		// Never base a new room on a tile directly adjoining the edge of the level
		if(getTile(randX + 1, randY) == NULL
			|| getTile(randX - 1, randY) == NULL
			|| getTile(randX, randY + 1) == NULL
			|| getTile(randX, randY - 1) == NULL) 
		{
			failedAttempts++;
			continue;
		}

		// Check the number of neighbours, and store the relative direction the room should be generated
		// in
		if(getTile(randX + 1, randY)->passable()) {
			numNeighbouringPassable++;
			generateDir = DIR_WEST;
		} else if(getTile(randX - 1, randY)->passable()) {
			numNeighbouringPassable++;
			generateDir = DIR_EAST;
		} else if(getTile(randX, randY + 1)->passable()) {
			numNeighbouringPassable++;
			generateDir = DIR_NORTH;
		} else if(getTile(randX, randY - 1)->passable()) {
			numNeighbouringPassable++;
			generateDir = DIR_SOUTH;
		}

		if(numNeighbouringPassable != 1) {
			continue;
			failedAttempts++;
		}

		// Found a wall with one open neighbour, see if there's room to generate a room on the
		// opposite side of the free space.
		roomWidth = (rand() % roomVariance) + minRoomSize;
		roomHeight = (rand() % roomVariance) + minRoomSize;
		int topLeftX, topLeftY;

		if(generateDir == DIR_WEST) {
			topLeftX = randX - (roomWidth - 1);
			topLeftY = randY - (roomHeight / 2);
		} else if(generateDir == DIR_EAST) {
			topLeftX = randX;
			topLeftY = randY - (roomHeight / 2);
		} else if(generateDir == DIR_NORTH) {
			topLeftX = randX - (roomWidth / 2);
			topLeftY = randY - (roomHeight - 1);
		} else if(generateDir == DIR_SOUTH) {
			topLeftX = randX - (roomWidth / 2);
			topLeftY = randY;
		}

		if(isRectEmpty(topLeftX, topLeftY, roomWidth, roomHeight)) {
			// Space is available, generate the room and add a door
			getTile(randX, randY)->setDoor(true);

			// 50% chance the door is open
			getTile(randX, randY)->setPassable(rand() % 2 == 0);
			
			for(int i = topLeftX + 1; i < topLeftX + roomWidth - 1; i++) {
				for(int j = topLeftY + 1; j < topLeftY + roomHeight - 1; j++) {
					getTile(i, j)->setPassable(true);
				}
			}
			
			generatedRooms++;
			failedAttempts = 0;
			freeTiles -= (roomWidth * roomHeight);
		}
	}
}

bool Level::isRectEmpty(int cornerX, int cornerY, int width, int height) {
	if(cornerX < 0 || cornerX + width > this->width ||
		cornerY < 0 || cornerY + height > this->height) {
			return false;
	}

	for(int i = cornerX; i < cornerX + width; i++) {
		for(int j = cornerY; j < cornerY + height; j++) {
			Tile * curTile = getTile(i, j);
			if (curTile->passable()) {
				return false;
			}
		}
	}

	return true;
}


// ----------------- LevelGen Implementation ----------------- 

Level LevelGen::generateLevel(int width, int height, int numOfMonsters)
{
	Level newLevel = Level(width, height);
	return newLevel;
}