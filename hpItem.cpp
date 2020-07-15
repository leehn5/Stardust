#include "stdafx.h"
#include "hpItem.h"

HRESULT hpItem::init(POINT pos)
{
	_x = pos.x;
	_y = pos.y;

	_img = IMAGEMANAGER->findImage("hpItem");

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_currentFrameX = _frameCount = 0;

	_speed = 2.0f;
	_angle = PI;

	_itemType = ITEM_HP;

	return S_OK;
}

void hpItem::update()
{
	item::update();

	frameCount(8);
}
