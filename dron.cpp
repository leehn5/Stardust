#include "stdafx.h"
#include "dron.h"

HRESULT dron::init()
{

	return S_OK;
}

HRESULT dron::init(DRON_TYPE type)
{
	_x = 0.0f;
	_y = 0.0f;

	_type = type;

	_img = IMAGEMANAGER->findImage("dron");

	_frameCount = _currentFrameX = 0;

	return S_OK;
}

void dron::release()
{
}

void dron::update()
{
	frameCount(9);
}

void dron::render()
{
	_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
}
