#include "stdafx.h"
#include "chainSaw.h"

void chainSaw::update()
{
	frameCount(9);
	move();
}

void chainSaw::move()
{
	//if (KEYMANAGER->isStayKeyDown('Y')) _angle += 0.14f;
	//if (KEYMANAGER->isStayKeyDown('U')) _angle -= 0.14f;

	_x += cosf(_angle) * _speed;
	_y -= sinf(_angle) * _speed;

	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void chainSaw::draw()
{
	//Rectangle(getMemDC(), _rc);
	_img->rotateFrameRender(getMemDC(), getFloatCenterRect().x, getFloatCenterRect().y, _currentFrameX, _currentFrameY, _angle);
	//_img->frameRender(getMemDC(), getCenterRect().x, getCenterRect().y, _currentFrameX, _currentFrameY);
}

