#pragma once
#include "enemy.h"

class minion2 : public enemy
{
public:
	minion2() { _currentHP = _maxHP = 1; };
	~minion2() {};

	virtual void update();
	virtual void move();
};

