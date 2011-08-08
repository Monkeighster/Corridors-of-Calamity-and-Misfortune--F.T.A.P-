#include "Character.h"
#include <cstdlib>

Character::Character(int maxHp, Tile * startPosition) :
	currentHp(maxHp), maxHp(maxHp), position(startPosition)
{
}

void Character::setPosition(Tile * position) 
{
	this->position = position;
}

Tile * Character::getPosition() const
{
	return this->position;
}

Player::Player(int maxHp) : Character(maxHp, NULL)
{
}