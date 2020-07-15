#include "stdafx.h"
#include "twoFire.h"

void twoFire::update()
{
	frameCount(9);
	move();
}

void twoFire::move()
{
	_moveTime++;

	if (_moveTime > 130)
	{
		//_angle = 7 * PI / 4;
		_angle = PI + (2.1f * _dir);
		_speed = 2.3;
	}
	if (_moveTime > 210)
	{
		_angle = PI;
		_speed = 2.0f;
	}
	if (_moveTime > 310)
	{
		_angle = PI - (1.57f * _dir);
	}
	if(_moveTime > 480) _angle = PI;

	_x += cosf(_angle) * _speed;
	_y -= sinf(_angle) * _speed;

	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}
