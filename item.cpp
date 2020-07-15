#include "stdafx.h"
#include "item.h"

HRESULT item::init()
{
	return S_OK;
}

HRESULT item::init(POINT pos)
{
	return S_OK;
}

void item::release()
{
}

void item::update()
{
	move();
}

void item::render()
{
	//Rectangle(getMemDC(), _rc);
	_img->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

void item::move()
{
	_x += cosf(_angle) * _speed;
	_y -= sinf(_angle) * _speed;

	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}
