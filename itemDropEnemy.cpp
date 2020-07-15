#include "stdafx.h"
#include "itemDropEnemy.h"

void itemDropEnemy::update()
{
	frameCount(9);
	move();
}

void itemDropEnemy::move()
{
	_x += cosf(_angle) * _speed;
	_y -= sinf(_angle) * _speed;

	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}
