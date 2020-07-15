#include "stdafx.h"
#include "effect.h"

HRESULT effect::init()
{
	return S_OK;
}

HRESULT effect::init(const char * imageName, POINT pos, int frameSpeed)
{
	_x = pos.x;
	_y = pos.y;

	_img = IMAGEMANAGER->findImage(imageName);

	_frameCount = _currentFrameX = 0;

	_frameSpeed = frameSpeed;

	return S_OK;
}

void effect::release()
{
}

void effect::update()
{
	frameCount(_frameSpeed);
}

void effect::render()
{
	_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
}

bool effect::isAnyEnd()
{
	if (_currentFrameX >= _img->getMaxFrameX()) return true;
	return false;
}
