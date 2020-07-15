#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"
#include "itemManager.h"
#include "effectManager.h"

enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	_bullet = new bullet;
	_bullet->init("enemyBullet", 3000);

	_gameFrame = 0;
	_enemyFrame = 0;
	_rndEnemyAppear = RND->getFromIntTo(50, 100);

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	_gameFrame++;

	// boss 출현
	if (_vMinion.size() <= 0 && _gameFrame > 3000)
	{
		if(_vBoss.size() <= 0) setBoss();
	}

	if (_gameFrame < 3000)
	{
		_enemyFrame++;

		// FIXME : 적 랜덤으로 출현하는데 좀 더 매끄럽게 출현하도록 수정하기
		if (_enemyFrame % _rndEnemyAppear == 0)
		{
			//int rnd = RND->getInt(15);
			//
			//switch (rnd)
			//{
			//case 3: _enemyType = ENEMY_ITEM_DROP; break;
			//default: _enemyType = RND->getFromIntTo(ENEMY_MINION1, ENEMY_END); break;
			//}

			_enemyType = ENEMY_ITEM_DROP;

			setMinion();
			//_rndEnemyAppear = RND->getFromIntTo(150, 250); // 이것도 아닌 거 같음
			_rndEnemyAppear = RND->getFromIntTo(40, 60); // 이것도 아닌 거 같음
			_enemyFrame = 0;
		}
	}

	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
		if ((*_viMinion)->getEnemyType() == ENEMY_CHAIN_SAW) 
			(*_viMinion)->setAngle(getAngle((*_viMinion)->getRect().left, (*_viMinion)->getRect().top, _player->getCenterPosition().x, _player->getCenterPosition().y));
	}

	for (_viBoss = _vBoss.begin(); _viBoss != _vBoss.end(); ++_viBoss)
	{
		(*_viBoss)->update();
	}

	enemyToBeErase();

	_bullet->update();

	if(!_player->isDead()) minionBulletFire();

	collision();

	if (KEYMANAGER->isOnceKeyDown('Q') && _enemyType > 0) _enemyType--;
	if (KEYMANAGER->isOnceKeyDown('W') && _enemyType < ENEMY_END - 1) _enemyType++;
	if (KEYMANAGER->isOnceKeyDown('E')) setMinion();
}

void enemyManager::render()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}

	for (_viBoss = _vBoss.begin(); _viBoss != _vBoss.end(); ++_viBoss)
	{
		(*_viBoss)->render();
	}

	_bullet->render();

	//char str[128];
	//sprintf_s(str, "enemy : %d", _vMinion.size());
	//TextOut(getMemDC(), 10, 150, str, strlen(str));

	//sprintf_s(str, "gameFrame : %d", _gameFrame);
	//TextOut(getMemDC(), 10, 180, str, strlen(str));
}

void enemyManager::setMinion()
{
	if (_enemyType == ENEMY_ITEM_DROP)
	{
		float _rndPosY = RND->getFromFloatTo(100, WINSIZEY - 100);
		enemy* enemy;
		enemy = new itemDropEnemy;
		enemy->init("itemDropEnemy", PointFloatMake(WINSIZEX, _rndPosY), (ENEMY_TYPE)_enemyType);
		_vMinion.push_back(enemy);
	}
	else if (_enemyType == ENEMY_MINION1)
	{
		enemy* enemy1;
		enemy1 = new minion2;
		enemy1->init("enemy1", PointFloatMake(WINSIZEX, WINSIZEY / 2 + 100), (ENEMY_TYPE)_enemyType);
		_vMinion.push_back(enemy1);

		enemy1 = new minion2;
		enemy1->init("enemy1", PointFloatMake(WINSIZEX, WINSIZEY / 2 - 100), (ENEMY_TYPE)_enemyType, -1);
		_vMinion.push_back(enemy1);
	}
	else if (_enemyType == ENEMY_CHAIN_SAW)
	{
		enemy* enemy;
		enemy = new chainSaw;
		enemy->init("enemy_chainSaw", PointFloatMake(WINSIZEX, WINSIZEY / 2 + 100), (ENEMY_TYPE)_enemyType);

		_vMinion.push_back(enemy);
	}
	else if (_enemyType == ENEMY_TWO_FIRE)
	{
		enemy* enemy;
		enemy = new twoFire;
		enemy->init("enemy_twoFire", PointFloatMake(WINSIZEX, WINSIZEY / 2 - 100), (ENEMY_TYPE)_enemyType);
		_vMinion.push_back(enemy);

		enemy = new twoFire;
		enemy->init("enemy_twoFire", PointFloatMake(WINSIZEX, WINSIZEY / 2 + 100), (ENEMY_TYPE)_enemyType, -1);
		_vMinion.push_back(enemy);
	}
	else if (_enemyType == ENEMY_GREEN)
	{
		float _rndPosY = RND->getFromFloatTo(100, WINSIZEY - 100);
		enemy* enemy;
		enemy = new enemyGreen;
		enemy->init("enemy_green", PointFloatMake(WINSIZEX, _rndPosY), (ENEMY_TYPE)_enemyType);
		_vMinion.push_back(enemy);
	}
}

void enemyManager::setBoss()
{
	boss* b = new boss;
	b->init("boss");
	b->linkedPlayer(_player);
	b->linkedEffect(_effectMgr);

	_vBoss.push_back(b);
}

void enemyManager::minionBulletFire()
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();

			if ((*_viMinion)->getEnemyType() == ENEMY_TWO_FIRE)
			{
				_bullet->bulletFire(rc.left - 7, rc.top + 25,
					getAngle((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2, _player->getCenterRect().x, _player->getCenterRect().y), 7.0f);

				_bullet->bulletFire(rc.left - 7, rc.bottom - 10,
					getAngle((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2, _player->getCenterRect().x, _player->getCenterRect().y), 7.0f);
			}
			else if ((*_viMinion)->getEnemyType() == ENEMY_MINION1 || (*_viMinion)->getEnemyType() == ENEMY_GREEN)
			{
				_bullet->bulletFire(rc.left - 7, rc.top + (rc.bottom - rc.top) / 2,
					getAngle((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2, _player->getCenterRect().x, _player->getCenterRect().y), 7.0f);
			}
		}
	}
}

void enemyManager::removeMinion(int arrNum)
{
	_vMinion.erase(_vMinion.begin() + arrNum);
}

void enemyManager::removeBoss(int arrNum)
{
	_vBoss.erase(_vBoss.begin() + arrNum);
}

void enemyManager::collision()
{
	for (int i = 0; i < _bullet->getBullet()->getUsedPoolSize(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_bullet->getBullet()->getUsedObject(i)->rc, &_player->getRect()))
		{
			//_effectMgr->setEffect("smallEffect", PointMake(_bullet->getBullet()->getUsedObject(i)->x - 5, _bullet->getBullet()->getUsedObject(i)->y), 5);
			_effectMgr->setEffect("smallEffect", PointMake(_bullet->getBullet()->getUsedObject(i)->rc.left, _bullet->getBullet()->getUsedObject(i)->rc.top), 5);
			_player->hitProcessing(1, 80);
			_bullet->getBullet()->colInsert(i);
			break;
		}
	}
}

void enemyManager::enemyToBeErase()
{
	for (int i = 0; i < _vMinion.size(); i++)
	{
		// 화면 왼쪽 밖으로 나간 적
		if (_vMinion[i]->getRect().right < 0) removeMinion(i);
		
		// 피가 다 닳아 죽은 적
		if (_vMinion.size() > 0 && _vMinion[i]->isDead())
		{
			switch (_vMinion[i]->getEnemyType())
			{
			case ENEMY_ITEM_DROP:
				_effectMgr->setEffect("itemEnemyEffect", PointMake(_vMinion[i]->getRect().left - 35, _vMinion[i]->getRect().top - 25), 5);
				_itemMgr->setItem(PointMake(_vMinion[i]->getRect().left + (_vMinion[i]->getRect().right - _vMinion[i]->getRect().left) / 2,
					_vMinion[i]->getRect().top + (_vMinion[i]->getRect().bottom - _vMinion[i]->getRect().top) / 2));
				_player->setScore(200);
				break;
			case ENEMY_MINION1:
				_effectMgr->setEffect("enemyDeadEffect", PointMake(_vMinion[i]->getRect().left - 35, _vMinion[i]->getRect().top - 25), 5);
				_player->setScore(120);
				break;
			case ENEMY_CHAIN_SAW:
				_effectMgr->setEffect("chainDeadEffect", PointMake(_vMinion[i]->getRect().left - 17, _vMinion[i]->getRect().top - 15), 5);
				_player->setScore(50);
				break;
			case ENEMY_TWO_FIRE:
				_effectMgr->setEffect("enemyDeadEffect", PointMake(_vMinion[i]->getRect().left - 35, _vMinion[i]->getRect().top - 25), 5);
				_player->setScore(150);
				break;
			case ENEMY_GREEN:
				_effectMgr->setEffect("enemyDeadEffect", PointMake(_vMinion[i]->getRect().left - 35, _vMinion[i]->getRect().top - 25), 5);
				_player->setScore(100);
				break;
			default:
				break;
			}
			
			removeMinion(i);
		}
	}

	for (int i = 0; i < _vBoss.size(); i++)
	{
		if (_vBoss.size() > 0 && _vBoss[i]->isDead())
		{
			_effectMgr->setEffect("enemyDeadEffect", PointMake(_vBoss[i]->getRect().left - 35, _vBoss[i]->getRect().top - 25), 5);
			_effectMgr->setEffect("enemyDeadEffect", PointMake(_vBoss[i]->getRect().left + 35, _vBoss[i]->getRect().top + 25), 5);
			_effectMgr->setEffect("enemyDeadEffect", PointMake(_vBoss[i]->getRect().right - 25, _vBoss[i]->getRect().top + 45), 5);
			_player->setScore(120);
			removeBoss(i);
		}
	}
}
