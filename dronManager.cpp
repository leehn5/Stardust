#include "stdafx.h"
#include "dronManager.h"
#include "enemyManager.h"
#include "effectManager.h"

dronManager::dronManager()
{
}

dronManager::~dronManager()
{
}

HRESULT dronManager::init()
{
	_bullet = new bullet;
	_bullet->init("dronBullet", 1000);

	_bullet2 = new bullet;
	_bullet2->init("dronBullet2", 2000);

	_fireCount = 0;

	return S_OK;
}

void dronManager::release()
{
}

void dronManager::update()
{
	for (_viDron = _vDron.begin(); _viDron != _vDron.end(); ++_viDron)
	{
		(*_viDron)->update();
	}
	dronMove();
	dronFire();

	_bullet->update();
	_bullet2->update();

	collision();
}

void dronManager::render()
{
	for (_viDron = _vDron.begin(); _viDron != _vDron.end(); ++_viDron)
	{
		(*_viDron)->render();
	}

	_bullet->render();
	_bullet2->render();
}

void dronManager::dronFire()
{
	if (isFireCount())
	{
		for (int i = 0; i < _vDron.size(); i++)
		{
			if (_vDron[i]->getDronType() == DRON_NORMAL)
			{
				_bullet->bulletFire(_vDron[i]->getPosition().x + _vDron[i]->getImage()->getFrameWidth(),
					_vDron[i]->getPosition().y + _vDron[i]->getImage()->getFrameHeight() / 2,
					PI2, 3.5f);
			}
			if (_vDron[i]->getDronType() == DRON_SIX_DIRECTION)
			{
				_bullet2->bulletFire(_vDron[i]->getPosition().x + _vDron[i]->getImage()->getFrameWidth() / 2,
					_vDron[i]->getPosition().y + _vDron[i]->getImage()->getFrameHeight() / 2,
					PI2, 3.5f);

				_bullet2->bulletFire(_vDron[i]->getPosition().x + _vDron[i]->getImage()->getFrameWidth() / 2,
					_vDron[i]->getPosition().y + _vDron[i]->getImage()->getFrameHeight() / 2,
					PI / 4, 3.5f);

				_bullet2->bulletFire(_vDron[i]->getPosition().x + _vDron[i]->getImage()->getFrameWidth() / 2,
					_vDron[i]->getPosition().y + _vDron[i]->getImage()->getFrameHeight() / 2,
					7 * PI / 4, 3.5f);

				_bullet2->bulletFire(_vDron[i]->getPosition().x + _vDron[i]->getImage()->getFrameWidth() / 2,
					_vDron[i]->getPosition().y + _vDron[i]->getImage()->getFrameHeight() / 2,
					3 * PI / 2, 3.5f);

				_bullet2->bulletFire(_vDron[i]->getPosition().x + _vDron[i]->getImage()->getFrameWidth() / 2,
					_vDron[i]->getPosition().y + _vDron[i]->getImage()->getFrameHeight() / 2,
					5 * PI / 4, 3.5f);

				_bullet2->bulletFire(_vDron[i]->getPosition().x + _vDron[i]->getImage()->getFrameWidth() / 2,
					_vDron[i]->getPosition().y + _vDron[i]->getImage()->getFrameHeight() / 2,
					PI, 3.5f);

				_bullet2->bulletFire(_vDron[i]->getPosition().x + _vDron[i]->getImage()->getFrameWidth() / 2,
					_vDron[i]->getPosition().y + _vDron[i]->getImage()->getFrameHeight() / 2,
					3 * PI / 4, 3.5f);

				_bullet2->bulletFire(_vDron[i]->getPosition().x + _vDron[i]->getImage()->getFrameWidth() / 2,
					_vDron[i]->getPosition().y + _vDron[i]->getImage()->getFrameHeight() / 2,
					PI / 2, 3.5f);
			}
		}
	}
}

void dronManager::dronMove()
{
	for (int i = 0; i < _vDron.size(); i++)
	{
		if (i == 0)
		{
			_vDron[i]->setX(_targetPos.x - 15);
			_vDron[i]->setY(_targetPos.y - 50);
		}
		if (i == 1)
		{
			_vDron[i]->setX(_targetPos.x - 15);
			_vDron[i]->setY(_targetPos.y + 35);
		}
		if (i == 2)
		{
			_vDron[i]->setX(_targetPos.x - 60);
			_vDron[i]->setY(_targetPos.y - 80);
		}
		if (i == 3)
		{
			_vDron[i]->setX(_targetPos.x - 60);
			_vDron[i]->setY(_targetPos.y + 65);
		}
	}
}

void dronManager::setDron()
{
	if (_vDron.size() > 3) return;

	if (_vDron.size() < 2)
	{
		dron* d = new dron;
		d->init(DRON_NORMAL);
		_vDron.push_back(d);
	}
	else
	{
		dron* d = new dron;
		d->init(DRON_SIX_DIRECTION);
		_vDron.push_back(d);
	}
}

void dronManager::collision()
{
	RECT temp;
	for (int i = 0; i < _em->getVMinion().size(); i++)
	{
		for (int j = 0; j < _bullet->getBullet()->getUsedPoolSize(); j++)
		{
			if (IntersectRect(&temp, &_bullet->getBullet()->getUsedObject(j)->rc, &_em->getVMinion()[i]->getRect()))
			{
				_effect->setEffect("smallEffect", PointMake(_bullet->getBullet()->getUsedObject(j)->x - 10, _bullet->getBullet()->getUsedObject(j)->y - 10), 5);
				_em->getVMinion()[i]->hitProcessing(1);
				_bullet->getBullet()->colInsert(j);

				break;
		
			}
		}
		for (int j = 0; j < _bullet2->getBullet()->getUsedPoolSize(); j++)
		{
			if (IntersectRect(&temp, &_bullet2->getBullet()->getUsedObject(j)->rc, &_em->getVMinion()[i]->getRect()))
			{
				_effect->setEffect("smallEffect", PointMake(_bullet2->getBullet()->getUsedObject(j)->x - 10, _bullet2->getBullet()->getUsedObject(j)->y - 10), 5);
				_em->getVMinion()[i]->hitProcessing(1);
				_bullet2->getBullet()->colInsert(j);

				break;
			}
		}
	}

	for (int i = 0; i < _em->getVBoss().size(); i++)
	{
		for (int j = 0; j < _bullet->getBullet()->getUsedPoolSize(); j++)
		{
			if (IntersectRect(&temp, &_bullet->getBullet()->getUsedObject(j)->rc, &_em->getVBoss()[i]->getRect()))
			{
				_effect->setEffect("smallEffect", PointMake(_bullet->getBullet()->getUsedObject(j)->x - 10, _bullet->getBullet()->getUsedObject(j)->y - 10), 5);
				_em->getVBoss()[i]->hitProcessing(1);
				_bullet->getBullet()->colInsert(j);

				break;
			}
		}
		for (int j = 0; j < _bullet2->getBullet()->getUsedPoolSize(); j++)
		{
			if (IntersectRect(&temp, &_bullet2->getBullet()->getUsedObject(j)->rc, &_em->getVBoss()[i]->getRect()))
			{
				_effect->setEffect("smallEffect", PointMake(_bullet2->getBullet()->getUsedObject(j)->x - 10, _bullet2->getBullet()->getUsedObject(j)->y - 10), 5);
				_em->getVBoss()[i]->hitProcessing(1);
				_bullet2->getBullet()->colInsert(j);

				break;
			}
		}
	}
}

void dronManager::removeAll()
{
	for (int i = 0; i < _vDron.size(); i++)
	{
		_vDron.erase(_vDron.begin() + i);
	}

	_vDron.clear();
}

bool dronManager::isFireCount()
{
	_fireCount++;

	if (_fireCount % 100 == 0)
	{
		_fireCount = 0;

		return true;
	}

	return false;
}
