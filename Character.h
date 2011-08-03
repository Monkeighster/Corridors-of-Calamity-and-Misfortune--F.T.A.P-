#ifndef CHARACTER_H
#define CHARACTER_H

class Tile;

class Character
{
private:
	int currentHp; 
	int maxHp;
	Tile * position;

public:
	Character(int maxHp, Tile * startPosition);

	/** Sets the character's position to the specified tile */
	void setPosition(Tile * position);

	/** @return A reference to the character's current position (or NULL
	 * if no position is set) */
	Tile * getPosition();
};


class Player : public Character
{
private:

public:
	/** Constructor (defaults to NULL position) */
	Player(int maxHp);
};

#endif