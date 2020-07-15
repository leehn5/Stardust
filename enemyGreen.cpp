#include "stdafx.h"
#include "enemyGreen.h"

void enemyGreen::update()
{
	frameCount(9);
	move();
}

void enemyGreen::move()
{
	_x += cosf(_angle) * _speed;
	_y -= sinf(_angle) * _speed;

	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}
