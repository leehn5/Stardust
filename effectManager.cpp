#include "stdafx.h"
#include "effectManager.h"

effectManager::effectManager()
{
}

effectManager::~effectManager()
{
}

HRESULT effectManager::init()
{
	return S_OK;
}

void effectManager::release()
{
}

void effectManager::update()
{
	for (int i = 0; i < _vEffect.size(); i++)
	{
		_vEffect[i]->update();
		if (_vEffect[i]->isAnyEnd()) removeEffect(i);
	}
}

void effectManager::render()
{
	for(_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->render();
	}
}

void effectManager::removeEffect(int num)
{
	_vEffect.erase(_vEffect.begin() + num);
}

void effectManager::setEffect(const char* imgName, POINT pos, int frameSpeed)
{
	effect* ef;
	ef = new effect;
	ef->init(imgName, PointMake(pos.x, pos.y), frameSpeed);

	_vEffect.push_back(ef);
}
