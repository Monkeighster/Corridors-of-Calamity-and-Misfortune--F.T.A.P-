#ifndef CHARACTER_H
#define CHARACTER_H

class Tile;

class Character
{
private:
	int currentHp; 
	int maxHp;
	Tile * tiles;

public:
	Character(int maxHp, Tile * startposition);
};


class Player : public Character
{
private:

public:

};

#endif