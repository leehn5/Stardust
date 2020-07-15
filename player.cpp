#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"
#include "effectManager.h"
#include "itemManager.h"
#include "dronManager.h"

player::player()
{
}

player::~player()
{
}

HRESULT player::init()
{
	
	return S_OK;
}

HRESULT player::init(const char * imageName)
{
	_x = 100.0f;
	_y = WINSIZEY / 2;
	_speed = 4.5f;

	_img = IMAGEMANAGER->findImage(imageName);
	//_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	_rc = RectMake(_x + 15, _y + 10, _img->getFrameWidth() - 13, _img->getFrameHeight() - 10);

	_bullet = new bullet;
	_bullet->init("playerBullet", 3000);

	_bullet2 = new bullet;
	_bullet2->init("playerBullet2", 3000);

	_bulletSpeed = 4.5f;

	_currentHP = _maxHP = 6;

	_alpha = 255;
	_bulletAngle = 0.0f;

	_frameCount = _currentFrameX = _score = 0;

	_bulletType = BULLET_NORMAL;

	_deadTimer = 0;
	_isDead = false;

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	frameCount(9);
	keycontrol();
	_rc = RectMake(_x + 15, _y + 10, _img->getFrameWidth() - 13, _img->getFrameHeight() - 10);

	_bullet->update();
	_bullet2->update();

	_dronMgr->setTargetPosition(PointFloatMake(_x + _img->getFrameWidth() / 2, _y + _img->getFrameHeight() / 2));

	collision();

	alphaBlending();

	if (isDead())
	{
		_dronMgr->removeAll();

		_deadTimer++;
		if (_deadTimer > 1 && _deadTimer < 3) _effect->setEffect("playerDeadEffect", PointMake(_x - 10, _y - 10), 5);
		if (_deadTimer > 250) _isDead = true;
	}
}

void player::render()
{
	_bullet->rotateRender();
	_bullet2->render();

	//Rectangle(getMemDC(), _rc);

	//_img->alphaFrameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY, _alpha);
	if(!isDead()) _img->alphaFrameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY, _alpha);

	//char str[128];
	//sprintf_s(str, "%d", _currentHP);
	//TextOut(getMemDC(), WINSIZEX / 2, 100, str, strlen(str));
}

void player::hitProcessing(int atk, int timer)
{
	if (_alpha != 255) return;

	_alphaTimer = timer;
	hitDamage(atk);
}

void player::keycontrol()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _x > 0.0f) _x -= _speed;
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _y > 0.0f) _y -= _speed;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _x + _img->getFrameWidth() < (WINSIZEX / 3) * 2) _x += _speed/2;
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _y + _img->getFrameHeight() < WINSIZEY) _y += _speed * 1.5f;

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && !isDead())
	{
		switch (_bulletType)
		{
		case BULLET_NORMAL:
			_bullet->bulletFire(_rc.right + 10, _y + _img->getFrameHeight() / 2, PI2, _bulletSpeed);
			break;
		case BULLET_THREE:
			_bulletAngle = PI2 - 0.1f;
			for (int i = 0; i < 3; i++)
			{
				_bullet->bulletFire(_rc.right + 10, _y + _img->getFrameHeight() / 2, _bulletAngle, _bulletSpeed + 0.5f);
				_bulletAngle += 0.1f;
			}
			break;
		case BULLET_FIVE:
			_bulletAngle = PI2 - 0.1f;
			for (int i = 0; i < 2; i++)
			{
				if (i == 0) _bullet2->bulletFire(_rc.right - 5, _y + _img->getFrameHeight() / 2 + 25, _bulletAngle, _bulletSpeed + 2.0f);
				else _bullet2->bulletFire(_rc.right - 5, _y + _img->getFrameHeight() / 2 - 35, _bulletAngle, _bulletSpeed + 2.0f);
				_bulletAngle += 0.2f;
			}
			_bullet->bulletFire(_rc.right + 15, _y + _img->getFrameHeight() / 2 + 15, PI2, _bulletSpeed + 2.0f);
			_bullet->bulletFire(_rc.right + 15, _y + _img->getFrameHeight() / 2, PI2, _bulletSpeed + 2.0f);
			_bullet->bulletFire(_rc.right + 15, _y + _img->getFrameHeight() / 2 - 15, PI2, _bulletSpeed + 2.0f);
			break;
		default:
			break;
		}
	}

	// HP test
	//if (KEYMANAGER->isOnceKeyDown('P') && _currentHP < 6) _currentHP++;
	//if (KEYMANAGER->isOnceKeyDown('O') && _currentHP > 0) _currentHP--;

	// bullet type test
	//if (KEYMANAGER->isOnceKeyDown('P')) _dronMgr->setDron();
	if (KEYMANAGER->isOnceKeyDown('P') && _bulletType < BULLET_FIVE) _bulletType++;
	if (KEYMANAGER->isOnceKeyDown('O') && _bulletType > BULLET_NORMAL) _bulletType--;
}

void player::collision()
{
	RECT temp;
	// enemy¶û player ÃÑ¾Ë°ú Ãæµ¹
	for (int i = 0; i < _em->getVMinion().size(); i++)
	{
		for (int j = 0; j < _bullet->getBullet()->getUsedPoolSize(); j++)
		{
			if (IntersectRect(&temp, &_bullet->getBullet()->getUsedObject(j)->rc, &_em->getVMinion()[i]->getRect()))
			{
				_effect->setEffect("smallEffect", PointMake(_bullet->getBullet()->getUsedObject(j)->x - 10, _bullet->getBullet()->getUsedObject(j)->y - 10), 5);
				_bullet->getBullet()->colInsert(j);     
				_em->getVMinion()[i]->hitProcessing(1);

				break;
			}
		}
	}

	// enemy¶û player bullet2 °ú Ãæµ¹
	for (int i = 0; i < _em->getVMinion().size(); i++)
	{
		for (int j = 0; j < _bullet2->getBullet()->getUsedPoolSize(); j++)
		{
			if (IntersectRect(&temp, &_bullet2->getBullet()->getUsedObject(j)->rc, &_em->getVMinion()[i]->getRect()))
			{
				_effect->setEffect("smallEffect", PointMake(_bullet2->getBullet()->getUsedObject(j)->x - 10, _bullet2->getBullet()->getUsedObject(j)->y - 10), 5);
				_bullet2->getBullet()->colInsert(j);
				_em->getVMinion()[i]->hitProcessing(1);

				break;
			}
		}
	}

	// boss¶û player bullet °ú Ãæµ¹
	for (int i = 0; i < _em->getVBoss().size(); i++)
	{
		for (int j = 0; j < _bullet->getBullet()->getUsedPoolSize(); j++)    
		{
			if (_em->getVBoss()[i]->getIsHitOk())
			{
				if (IntersectRect(&temp, &_bullet->getBullet()->getUsedObject(j)->rc, &_em->getVBoss()[i]->getRect()))
				{
					_effect->setEffect("smallEffect", PointMake(_bullet->getBullet()->getUsedObject(j)->x - 10, _bullet->getBullet()->getUsedObject(j)->y - 10), 5);
					_bullet->getBullet()->colInsert(j);
					_em->getVBoss()[i]->hitProcessing(1);

					break;
				}
			}
		}
	}

	// boss¶û player bullet2 °ú Ãæµ¹
	for (int i = 0; i < _em->getVBoss().size(); i++)
	{
		for (int j = 0; j < _bullet2->getBullet()->getUsedPoolSize(); j++)
		{
			if (_em->getVBoss()[i]->getIsHitOk())
			{
				if (IntersectRect(&temp, &_bullet2->getBullet()->getUsedObject(j)->rc, &_em->getVBoss()[i]->getRect()))
				{
					_effect->setEffect("smallEffect", PointMake(_bullet2->getBullet()->getUsedObject(j)->x - 10, _bullet2->getBullet()->getUsedObject(j)->y - 10), 5);
					_bullet2->getBullet()->colInsert(j);
					_em->getVBoss()[i]->hitProcessing(1);

					break;
				}
			}
		}
	}

	// enemy¶û player Ãæµ¹
	for (int i = 0; i < _em->getVMinion().size(); i++)
	{
		if (IntersectRect(&temp, &_em->getVMinion()[i]->getRect(), &_rc))
		{
			hitProcessing(1, 80);
			break;
		}
	}
}

void player::setBulletType(int value)
{
	if (_bulletType >= BULLET_FIVE) return;
	_bulletType += value;
}
