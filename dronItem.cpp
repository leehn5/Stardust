#include "stdafx.h"
#include "dronItem.h"

HRESULT dronItem::init(POINT pos)
{
	_x = pos.x;
	_y = pos.y;

	_img = IMAGEMANAGER->findImage("dronItem");

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_currentFrameX = _frameCount = 0;

	_speed = 2.0f;
	_angle = PI;

	_itemType = ITEM_DRON;

	return S_OK;
}

void dronItem::update()
{
	item::update();

	frameCount(8);
}
