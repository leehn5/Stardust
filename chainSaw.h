#pragma once
#include "enemy.h"

class chainSaw : public enemy
{
public:
	chainSaw() { _currentHP = _maxHP = 3; };
	~chainSaw() {};

	virtual void update();
	virtual void move();
	virtual void draw();
};

