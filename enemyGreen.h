#pragma once
#include "enemy.h"

class enemyGreen : public enemy
{
public:
	enemyGreen() { _currentHP = _maxHP = 1; };
	~enemyGreen() {};

	virtual void update();
	virtual void move();
};

