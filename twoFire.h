#pragma once
#include "enemy.h"
class twoFire : public enemy
{
public:
	twoFire() { _currentHP = _maxHP = 4; };
	~twoFire() {};

	virtual void update();
	virtual void move();
};

