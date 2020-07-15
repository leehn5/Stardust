#include "stdafx.h"
#include "minion2.h"

void minion2::update()
{
	frameCount(9);
	move();
}

void minion2::move()
{
	_moveTime++;

	if (_moveTime > 70)
	{
		_angle = PI - (0.8f * _dir);
		_speed = 2.3f;
	}
	if (_moveTime > 300)
	{
		_angle = PI;
		_speed = 2;
	}
	if (_moveTime > 450) _angle = PI + (0.8f * _dir);
	if (_moveTime > 600) _angle = PI;
	
	_x += cosf(_angle) * _speed;
	_y -= sinf(_angle) * _speed;

	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}