#include "stdafx.h"
#include "object.h"

object::object()
{
}

object::~object()
{
}

HRESULT object::init()
{

	return S_OK;
}

void object::release()
{
}

void object::update()
{
	
}

void object::render()
{
}

void object::frameCount(int time)
{
	_frameCount++;

	if (_frameCount % time == 0)
	{
		if (_currentFrameX >= _img->getMaxFrameX()) _currentFrameX = 0;

		_img->setFrameX(_currentFrameX);
		_currentFrameX++;
		_frameCount = 0;
	}
}

void object::alphaBlending()
{
	if (_alphaTimer < 0)
	{
		_alphaTimer = 0;
		_alpha = 255;
		return;
	}
	
	_alphaTimer--;

	_alpha -= 8;
	
	if (_alpha < 0) _alpha = 254;
}

void object::healHP(int value)
{
	if (_currentHP >= _maxHP) return;
	_currentHP += value;
}

void object::hitDamage(int atk)
{
	if (_currentHP <= 0) return;
	_currentHP -= atk;
}

void object::hitProcessing(int timer, int atk)
{

}

bool object::isDead()
{
	if (_currentHP <= 0) return true;
	return false;
}
