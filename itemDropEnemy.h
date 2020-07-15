#pragma once
#include "enemy.h"

class itemDropEnemy : public enemy
{
public:
	itemDropEnemy() { _currentHP = _maxHP = 5; };
	~itemDropEnemy() {};

	virtual void update();
	virtual void move();
};

