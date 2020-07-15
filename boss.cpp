#include "stdafx.h"
#include "boss.h"
#include "player.h"
#include "effectManager.h"

boss::boss()
{
}

boss::~boss()
{
}

HRESULT boss::init()
{
	return S_OK;
}

HRESULT boss::init(const char * imageName)
{
	_x = WINSIZEX;
	//_x = WINSIZEX/ 2;
	_y = WINSIZEY / 2 - 50;

	_img = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_bullet = new bullet;
	_bullet->init("bossBullet", 3000);

	_bulletSpeed = 3.5f;

	_currentHP = _maxHP = 30;

	_bulletAngle = PI;
	_bulletAngle2 = 0.0f;

	_frameCount = _currentFrameX = _fireCount = _fireTime = 0;

	_angle = PI;
	_speed = 0.0f;

	_pattern = PATTERN_NONE;

	_isFire = _isHitOk = false;

	_bulletTimer = _bulletMoveTime = 0.0f;

	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
	frameCount(5);
	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_bullet->update();

	move();

	collision();

	switch (_pattern)
	{
	case PATTERN_NORMAL_FIRE:
	{
		if (countFire(50, 5))
		{
			for (int i = 0; i < 30; i++)
			{
				_bullet->bulletFire(_fireCount, _x, _y + _img->getFrameHeight() / 2 - 9, _bulletAngle2 + _bulletAngle, 7.5f, BULLET_MOVE_NORMAL_ROTATION, true);
				_bulletAngle += (PI2 / 29);
				_bullet->setIsGo(true);
			}
			_bulletAngle2 += 0.35f;
		}
	}
	break;
	case PATTERN_ROTATE_FIRE:
	{
		if (countFire(60, 3))
		{
			if (_fireCount == 1 || _fireCount == 3)
			{
				for (int i = 0; i < 15; i++)
				{
					_bullet->bulletFire(_x + 75, _y + _img->getFrameHeight() / 2 - 9, _bulletAngle, _bulletSpeed, PointFloatMake(-3.0f, 3.0f), BULLET_MOVE_ROTATION, false);
					_bulletAngle += PI2 / 15;
				}
				for (int i = 0; i < 15; i++)
				{
					_bullet->bulletFire(_x + 50, _y + _img->getFrameHeight() / 2 - 9, _bulletAngle, _bulletSpeed, PointFloatMake(-3.0f, 2.0f), BULLET_MOVE_ROTATION, false);
					_bulletAngle += PI2 / 15;
				}
				for (int i = 0; i < 15; i++)
				{
					_bullet->bulletFire(_x + 25, _y + _img->getFrameHeight() / 2 - 9, _bulletAngle, _bulletSpeed, PointFloatMake(-3.0f, 1.0f), BULLET_MOVE_ROTATION, false);
					_bulletAngle += PI2 / 15;
				}
				for (int i = 0; i < 15; i++)
				{
					_bullet->bulletFire(_x, _y + _img->getFrameHeight() / 2 - 9, _bulletAngle, _bulletSpeed, PointFloatMake(-3.0f, 0.0f), BULLET_MOVE_ROTATION, false);
					_bulletAngle += PI2 / 15;
				}
				for (int i = 0; i < 15; i++)
				{
					_bullet->bulletFire(_x + 25, _y + _img->getFrameHeight() / 2 - 9, _bulletAngle, _bulletSpeed, PointFloatMake(-3.0f, -1.0f), BULLET_MOVE_ROTATION, false);
					_bulletAngle += PI2 / 15;
				}
				for (int i = 0; i < 15; i++)
				{
					_bullet->bulletFire(_x + 50, _y + _img->getFrameHeight() / 2 - 9, _bulletAngle, _bulletSpeed, PointFloatMake(-3.0f, -2.0f), BULLET_MOVE_ROTATION, false);
					_bulletAngle += PI2 / 15;
				}
				for (int i = 0; i < 15; i++)
				{
					_bullet->bulletFire(_x + 75, _y + _img->getFrameHeight() / 2 - 9, _bulletAngle, _bulletSpeed, PointFloatMake(-3.0f, -3.0f), BULLET_MOVE_ROTATION, false);
					_bulletAngle += PI2 / 15;
				}
			}
			else
			{
				for (int i = 0; i < 15; i++)
				{
					_bullet->bulletFire(_x + 50, _y + _img->getFrameHeight() / 2 - 9, _bulletAngle, _bulletSpeed, PointFloatMake(-3.0f, 2.5f), BULLET_MOVE_ROTATION, false);
					_bulletAngle += PI2 / 15;
				}
				for (int i = 0; i < 15; i++)
				{
					_bullet->bulletFire(_x + 25, _y + _img->getFrameHeight() / 2 - 9, _bulletAngle, _bulletSpeed, PointFloatMake(-3.0f, 1.5f), BULLET_MOVE_ROTATION, false);
					_bulletAngle += PI2 / 15;
				}
				for (int i = 0; i < 15; i++)
				{
					_bullet->bulletFire(_x, _y + _img->getFrameHeight() / 2 - 9, _bulletAngle, _bulletSpeed, PointFloatMake(-3.0f, 0.5f), BULLET_MOVE_ROTATION, false);
					_bulletAngle += PI2 / 15;
				}
				for (int i = 0; i < 15; i++)
				{
					_bullet->bulletFire(_x, _y + _img->getFrameHeight() / 2 - 9, _bulletAngle, _bulletSpeed, PointFloatMake(-3.0f, -0.5f), BULLET_MOVE_ROTATION, false);
					_bulletAngle += PI2 / 15;
				}
				for (int i = 0; i < 15; i++)
				{
					_bullet->bulletFire(_x + 25, _y + _img->getFrameHeight() / 2 - 9, _bulletAngle, _bulletSpeed, PointFloatMake(-3.0f, -1.5f), BULLET_MOVE_ROTATION, false);
					_bulletAngle += PI2 / 15;
				}
				for (int i = 0; i < 15; i++)
				{
					_bullet->bulletFire(_x + 50, _y + _img->getFrameHeight() / 2 - 9, _bulletAngle, _bulletSpeed, PointFloatMake(-3.0f, -2.5f), BULLET_MOVE_ROTATION, false);
					_bulletAngle += PI2 / 15;
				}
			}
		}
	}
	break;
	case PATTERN_ROTATE_FIRE2:
	{
		if (countFire(40, 5))
		{
			for (int i = 0; i < 25; i++)
			{
				_bullet->bulletFire(_fireCount, _x, _y + _img->getFrameHeight() / 2 - 9, _bulletAngle, _bulletSpeed, PointFloatMake(-3.0f, -3.0f - _fireCount), BULLET_MOVE_ROTATION2, false);
				_bulletAngle += PI2 / 25;
			}
		}
	}
	break;
	case PATTERN_SATELLITE_FIRE:
	{
		if (countFire(50, 1))
		{
			for (int i = 0; i < 15; i++)
			{
				_bullet->bulletFire(0, _x, _y + _img->getFrameHeight() / 2 - 9, i * 2 * PI / 15 + _bulletAngle, 45.5f, PointFloatMake(_x + _img->getFrameWidth() / 2, _y + _img->getFrameHeight() / 2), BULLET_MOVE_SATELLITE, false);
				_bullet->bulletFire(1, _x, _y + _img->getFrameHeight() / 2 - 9, i * 2 * PI / 15 + _bulletAngle, 45.5f, PointFloatMake(_x + _img->getFrameWidth() / 2, _y + _img->getFrameHeight() / 2), BULLET_MOVE_SATELLITE, false);
				_bullet->bulletFire(2, _x, _y + _img->getFrameHeight() / 2 - 9, i * 2 * PI / 15 + _bulletAngle, 65.5f, PointFloatMake(_x + _img->getFrameWidth() / 2, _y + _img->getFrameHeight() / 2), BULLET_MOVE_SATELLITE, false);
				_bullet->bulletFire(3, _x, _y + _img->getFrameHeight() / 2 - 9, i * 2 * PI / 15 + _bulletAngle, 65.5f, PointFloatMake(_x + _img->getFrameWidth() / 2, _y + _img->getFrameHeight() / 2), BULLET_MOVE_SATELLITE, false);
				
				_bullet->bulletFire(4, _x, _y + _img->getFrameHeight() / 2 - 9, i * 2 * PI / 15 + _bulletAngle, 65.5f, PointFloatMake(_x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2), BULLET_MOVE_SATELLITE, false);
				_bullet->bulletFire(6, _x, _y + _img->getFrameHeight() / 2 - 9, i * 2 * PI / 15 + _bulletAngle, 65.5f, PointFloatMake(_x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2), BULLET_MOVE_SATELLITE, false);
				_bullet->bulletFire(8, _x, _y + _img->getFrameHeight() / 2 - 9, i * 2 * PI / 15 + _bulletAngle, 65.5f, PointFloatMake(_x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2), BULLET_MOVE_SATELLITE, false);
				_bullet->bulletFire(10, _x, _y + _img->getFrameHeight() / 2 - 9, i * 2 * PI / 15 + _bulletAngle, 45.5f, PointFloatMake(_x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2), BULLET_MOVE_SATELLITE, false);

				_bullet->bulletFire(5, _x, _y + _img->getFrameHeight() / 2 - 9, i * 2 * PI / 15 + _bulletAngle, 65.5f, PointFloatMake(_x - _img->getFrameWidth() / 2, _y + _img->getFrameHeight() + _img->getFrameHeight() / 2), BULLET_MOVE_SATELLITE, false);
				_bullet->bulletFire(7, _x, _y + _img->getFrameHeight() / 2 - 9, i * 2 * PI / 15 + _bulletAngle, 65.5f, PointFloatMake(_x - _img->getFrameWidth() / 2, _y + _img->getFrameHeight() + _img->getFrameHeight() / 2), BULLET_MOVE_SATELLITE, false);
				_bullet->bulletFire(9, _x, _y + _img->getFrameHeight() / 2 - 9, i * 2 * PI / 15 + _bulletAngle, 65.5f, PointFloatMake(_x - _img->getFrameWidth() / 2, _y + _img->getFrameHeight() + _img->getFrameHeight() / 2), BULLET_MOVE_SATELLITE, false);
				_bullet->bulletFire(11, _x, _y + _img->getFrameHeight() / 2 - 9, i * 2 * PI / 15 + _bulletAngle, 45.5f, PointFloatMake(_x - _img->getFrameWidth() / 2, _y + _img->getFrameHeight() + _img->getFrameHeight() / 2), BULLET_MOVE_SATELLITE, false);
			}
		}
	}
	break;
	case PATTERN_NONE:
		break;
	default:
		break;
	}

	_bullet->setTarget(PointFloatMake(_player->getPosition().x, _player->getPosition().y));
}

void boss::render()
{
	//Rectangle(getMemDC(), _rc);
	_img->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	_bullet->render();

	//char str[128];
	//sprintf_s(str, "%.f", _moveTime);
	//TextOut(getMemDC(), WINSIZEX / 2, 10, str, strlen(str));
	//
	//sprintf_s(str, "%d", _bullet->getBullet()->getSize());
	//TextOut(getMemDC(), WINSIZEX / 2, 30, str, strlen(str));
	//
	//sprintf_s(str, "%d", _fireCount);
	//TextOut(getMemDC(), WINSIZEX / 2, 80, str, strlen(str));

	//switch (_pattern)
	//{
	//case PATTERN_NORMAL_FIRE:		TextOut(getMemDC(), WINSIZEX / 2, 50, "PATTERN_NORMAL_FIRE", strlen("PATTERN_NORMAL_FIRE"));		break;
	//case PATTERN_ROTATE_FIRE:		TextOut(getMemDC(), WINSIZEX / 2, 50, "PATTERN_ROTATE_FIRE", strlen("PATTERN_ROTATE_FIRE"));		break;
	//case PATTERN_SATELLITE_FIRE:	TextOut(getMemDC(), WINSIZEX / 2, 50, "PATTERN_SATELLITE_FIRE", strlen("PATTERN_SATELLITE_FIRE"));	break;
	//case PATTERN_NONE:				TextOut(getMemDC(), WINSIZEX / 2, 50, "PATTERN_NONE", strlen("PATTERN_NONE"));						break;
	//}
}

void boss::move()
{
	_moveTime++;
	
	if (_moveTime > 400) _speed = 2.0f;
	if (_moveTime > 500) _speed = 1.5f;
	if (_moveTime > 580) _speed = 0.0f;
	if (_moveTime > 600) _isHitOk = true;

	if (_moveTime > 650)
	{
		if (!_player->isDead() && fire()) _pattern = RND->getInt(PATTERN_NONE);
	}

	if (KEYMANAGER->isOnceKeyDown('1')) _pattern = PATTERN_NORMAL_FIRE;
	if (KEYMANAGER->isOnceKeyDown('2')) _pattern = PATTERN_ROTATE_FIRE2;
	if (KEYMANAGER->isOnceKeyDown('3')) _pattern = PATTERN_SATELLITE_FIRE;
	if (KEYMANAGER->isOnceKeyDown('0')) _pattern = PATTERN_ROTATE_FIRE;
	
	_x += cosf(_angle) * _speed;
	_y -= sinf(_angle) * _speed;

	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void boss::collision()
{
	RECT temp;

	// boss bulletÀÌ¶û player Ãæµ¹
	for (int i = 0; i < _bullet->getBullet()->getUsedPoolSize(); i++)
	{
		if (IntersectRect(&temp, &_bullet->getBullet()->getUsedObject(i)->rc, &_player->getRect()))
		{
			_ef->setEffect("smallEffect", PointMake(_bullet->getBullet()->getUsedObject(i)->x - 15, _bullet->getBullet()->getUsedObject(i)->y), 5);
			//_player->hitProcessing(1, 80);
			_bullet->getBullet()->colInsert(i);
		}
	}

	// boss¶û player Ãæµ¹
	if (IntersectRect(&temp, &_rc, &_player->getRect()))
	{
		_player->hitProcessing(1, 80);
	}
}

bool boss::countFire(int time, int count)
{
	if (_pattern == PATTERN_NONE) return _isFire = false;

	_fireTime++;
	
	if (_fireCount >= count)
	{
		_pattern = PATTERN_NONE;
		_fireCount = 0;
		_fireTime = 0;

		_bulletAngle2 = 0.0f;
		return _isFire = false;
	}

	if (_fireTime % time == 0)
	{
		_fireTime = 0;
		_fireCount++;
		return _isFire = true;
	}
	return _isFire = false;
}

bool boss::fire()
{
	_bossFire++;

	if (_bossFire % 400 == 0)
	{
		_bossFire = 0;
		return true;
	}

	return false;
}
