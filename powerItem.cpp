#include "stdafx.h"
#include "powerItem.h"

HRESULT powerItem::init(POINT pos)
{
	_x = pos.x;
	_y = pos.y;

	_img = IMAGEMANAGER->findImage("powerItem");

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_currentFrameX = _frameCount = 0;

	_speed = 2.0f;
	_angle = PI;

	_itemType = ITEM_POWER;

	return S_OK;
}

void powerItem::update()
{
	item::update();

	frameCount(8);
}

