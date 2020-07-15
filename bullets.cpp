#include "stdafx.h"
#include "bullets.h"

void ObjectPool::CreatePool(int size)
{
	//_pool = new queue <tagBullet>;
	//pool->reserve(_size);
	_usedPool.reserve(size);
	for (int i = 0; i < size; i++)
	{
		tagBullet* obj = new tagBullet;
		obj->x = 0.0f;
		obj->y = 0.0f;
		obj->angle = 0.0f;
		obj->speed = 0.0f;

		_pool.push(obj);
	}
}

// 순서대로 차곡차곡 넣는다
// 화면밖으로 나갈 때 쓰라(충돌없이)
void ObjectPool::InssertQueue()
{
	//_pool.push(_usedPool.front());
	_pool.push(*_usedPool.begin());
	_usedPool.erase(_usedPool.begin());
}

// 충돌한 아이를 없애준다
void ObjectPool::colInsert(int num)
{
	//_pool.push(_usedPool[num]);
	_pool.push(*_usedPool.begin() + num);
	_usedPool.erase(_usedPool.begin() + num);
}

// fire할 때 
// 벡터에 넣는 대신 여기에다가 넣어요
void ObjectPool::setUsedObject()
{
	_usedPool.push_back(_pool.front());
	_pool.pop();
}

HRESULT bullet::init(const char * imageName, int size)
{
	_pool = new ObjectPool;
	_img = IMAGEMANAGER->findImage(imageName);
	_angle = 0;
	_pool->CreatePool(size);

	return S_OK;
}

void bullet::release()
{
	SAFE_DELETE(_img);
	SAFE_DELETE(_pool);
}

void bullet::update()
{
	bulletMove();
	_angle -= 1.75f;
}

void bullet::render()
{
	if (!_pool->getUsedPoolSize()) return;

	for (int i = 0; i < _pool->getUsedPoolSize(); i++)
	{
		//Rectangle(getMemDC(), _pool->getUsedObject(i)->rc);
		_img->render(getMemDC(), _pool->getUsedObject(i)->rc.left, _pool->getUsedObject(i)->rc.top);
	}
}

void bullet::rotateRender()
{
	if (!_pool->getUsedPoolSize()) return;
	for (int i = 0; i < _pool->getUsedPoolSize(); i++)
	{
		//Rectangle(getMemDC(), _pool->getUsedObject(i).rc);
		_img->rotateRender(getMemDC(), _pool->getUsedObject(i)->rc.left + _img->getWidth() / 2, _pool->getUsedObject(i)->rc.top + _img->getHeight() / 2, _angle);
	}

	//char str[128];
	//sprintf_s(str, "Pool Size : %d", _pool->getSize());
	//TextOut(getMemDC(), 200, 30, str, strlen(str));
	//
	//sprintf_s(str, "Used Pool Size : %d", _pool->getUsedPoolSize());
	//TextOut(getMemDC(), 200, 50, str, strlen(str));
}

void bullet::bulletFire(int id, float x, float y, float angle, float speed, BULLET_MOVE_TYPE moveType, bool isGo)
{
	_pool->getObject()->id = id;
	_pool->getObject()->x = x;
	_pool->getObject()->y = y;
	_pool->getObject()->angle = angle;
	_pool->getObject()->speed = speed;
	_pool->getObject()->moveType = moveType;
	_isGo = isGo;
	_pool->getObject()->touchPos = { 0.0f, 0.0f };
	_target = { 0.0f, 0.0f };
	_pool->getObject()->rc = RectMakeCenter(_pool->getObject()->x, _pool->getObject()->y, _img->getWidth(), _img->getHeight());

	_pool->setUsedObject();
}

void bullet::bulletFire(float x, float y, float angle, float speed, BULLET_MOVE_TYPE moveType, bool isGo)
{
	_pool->getObject()->x = x;
	_pool->getObject()->y = y;
	_pool->getObject()->angle = angle;
	_pool->getObject()->speed = speed;
	_pool->getObject()->moveType = moveType;
	_isGo = isGo;
	_pool->getObject()->touchPos = { 0.0f, 0.0f };
	_target = { 0.0f, 0.0f };
	_pool->getObject()->rc = RectMakeCenter(_pool->getObject()->x, _pool->getObject()->y, _img->getWidth(), _img->getHeight());

	_pool->setUsedObject();
}

void bullet::bulletFire(float x, float y, float angle, float speed, POINTFLOAT pos, BULLET_MOVE_TYPE moveType, bool isGo)
{
	_pool->getObject()->x = x;
	_pool->getObject()->y = y;
	_pool->getObject()->angle = angle;
	_pool->getObject()->speed = speed;
	_pool->getObject()->moveType = moveType;
	_isGo = isGo;
	_pool->getObject()->touchPos = pos;
	_pool->getObject()->timer = 0;
	_target = { 0.0f, 0.0f };
	_pool->getObject()->rc = RectMakeCenter(_pool->getObject()->x, _pool->getObject()->y, _img->getWidth(), _img->getHeight());

	_pool->setUsedObject();
}

void bullet::bulletFire(int id, float x, float y, float angle, float speed, POINTFLOAT pos, BULLET_MOVE_TYPE moveType, bool isGo)
{
	_pool->getObject()->id = id;
	_pool->getObject()->x = x;
	_pool->getObject()->y = y;
	_pool->getObject()->angle = angle;
	_pool->getObject()->speed = speed;
	_pool->getObject()->moveType = moveType;
	_isGo = isGo;
	_pool->getObject()->touchPos = pos;
	_pool->getObject()->timer = 0;
	_target = { 0.0f, 0.0f };
	_intercept1 = _slope1 = _intercept2 = _slope2 = 0.0f;
	_pool->getObject()->rc = RectMakeCenter(_pool->getObject()->x, _pool->getObject()->y, _img->getWidth(), _img->getHeight());

	_pool->setUsedObject();
}

void bullet::bulletMove()
{
	if (!_pool->getUsedPoolSize()) return;
	for (int i = _pool->getUsedPoolSize() -1; i >= 0; i--)
	{
		switch (_pool->getUsedObject(i)->moveType)
		{
		case BULLET_MOVE_NORMAL:
			_pool->getUsedObject(i)->x += cosf(_pool->getUsedObject(i)->angle) * _pool->getUsedObject(i)->speed;
			_pool->getUsedObject(i)->y -= sinf(_pool->getUsedObject(i)->angle) * _pool->getUsedObject(i)->speed;
			break;
		case BULLET_MOVE_NORMAL_ROTATION:
			_pool->getUsedObject(i)->x += cosf(_pool->getUsedObject(i)->angle) * _pool->getUsedObject(i)->speed;
			_pool->getUsedObject(i)->y -= sinf(_pool->getUsedObject(i)->angle) * _pool->getUsedObject(i)->speed;

			switch (_pool->getUsedObject(i)->id)
			{
			case 1:case 3:case 5: _pool->getUsedObject(i)->angle -= 0.01f; break;
			default: _pool->getUsedObject(i)->angle += 0.01f; break;
			}

			break;
		case BULLET_MOVE_ROTATION:
			_pool->getUsedObject(i)->timer++;

			_pool->getUsedObject(i)->x += cosf(_pool->getUsedObject(i)->angle) * _pool->getUsedObject(i)->speed + _pool->getUsedObject(i)->touchPos.x;
			_pool->getUsedObject(i)->y -= sinf(_pool->getUsedObject(i)->angle) * _pool->getUsedObject(i)->speed + _pool->getUsedObject(i)->touchPos.y;
			
			if (_pool->getUsedObject(i)->timer > 120) _pool->getUsedObject(i)->angle += 0.04f;
			else _pool->getUsedObject(i)->angle += 0.1f;
			break;
		case BULLET_MOVE_ROTATION2:
			_pool->getUsedObject(i)->timer++;

			if (_isGo)
			{
				_pool->getUsedObject(i)->x += cosf(_pool->getUsedObject(i)->angle) * (_pool->getUsedObject(i)->speed * 2);
				_pool->getUsedObject(i)->y -= sinf(_pool->getUsedObject(i)->angle) * (_pool->getUsedObject(i)->speed * 2);
				switch (_pool->getUsedObject(i)->id)
				{
				case 1:case 3:case 5: _pool->getUsedObject(i)->angle -= 0.01f; break;
				default: _pool->getUsedObject(i)->angle += 0.01f; break;
				}
			}
			else
			{
				_pool->getUsedObject(i)->x += cosf(_pool->getUsedObject(i)->angle) * _pool->getUsedObject(i)->speed;
				_pool->getUsedObject(i)->y -= sinf(_pool->getUsedObject(i)->angle) * _pool->getUsedObject(i)->speed;
				_pool->getUsedObject(i)->angle += 0.08f;

			}
			if (_pool->getUsedObject(i)->timer > 150) _isGo = true;

			break;
		case BULLET_MOVE_SATELLITE:

			_pool->getUsedObject(i)->timer++;

			if (_isGo)
			{
				switch (_pool->getUsedObject(i)->id)
				{
				case 4:case 6:case 8:case 10:
					 _pool->getUsedObject(i)->touchPos.x -= 13.0f;
					 _pool->getUsedObject(i)->touchPos.y = _slope1 * _pool->getUsedObject(i)->touchPos.x + _intercept1;

					if (_pool->getUsedObject(i)->id == 4)	// 위에 작은 왼쪽 대각선
					{
						_pool->getUsedObject(i)->x = _pool->getUsedObject(i)->touchPos.x + (+cosf(_pool->getUsedObject(i)->angle) * 30) *
							cosf(AXISANGLE/* -PI/10*/) + (-sinf(_pool->getUsedObject(i)->angle) * 90) * sinf(AXISANGLE/*-PI/10*/);
						_pool->getUsedObject(i)->y = _pool->getUsedObject(i)->touchPos.y + (-sinf(_pool->getUsedObject(i)->angle) * 90) *
							cosf(AXISANGLE/*- PI/10*/) - (+cosf(_pool->getUsedObject(i)->angle) * 30) *sinf(AXISANGLE/*-PI/10*/);
					}
					
					if (_pool->getUsedObject(i)->id == 6)	// 위에 작은 오른쪽 대각선
					{
						_pool->getUsedObject(i)->x = _pool->getUsedObject(i)->touchPos.x + (+cosf(_pool->getUsedObject(i)->angle) * 90)*
							cosf(AXISANGLE/*+PI/10*/) + (-sinf(_pool->getUsedObject(i)->angle) * 30) * sinf(AXISANGLE/*+PI/10*/);
						_pool->getUsedObject(i)->y = _pool->getUsedObject(i)->touchPos.y + (-sinf(_pool->getUsedObject(i)->angle) * 30) *
							cosf(AXISANGLE/*+PI/10*/) - (+cosf(_pool->getUsedObject(i)->angle) * 90) *sinf(AXISANGLE/*+PI/10*/);
					}
					if (_pool->getUsedObject(i)->id == 8)	// 위에 작은 세로
					{
						_pool->getUsedObject(i)->x = _pool->getUsedObject(i)->touchPos.x + (+cosf(_pool->getUsedObject(i)->angle) * 30);
						_pool->getUsedObject(i)->y = _pool->getUsedObject(i)->touchPos.y + (-sinf(_pool->getUsedObject(i)->angle) * 90);
					}
					if (_pool->getUsedObject(i)->id == 10)	// 위에 작은 가로
					{
						_pool->getUsedObject(i)->x = _pool->getUsedObject(i)->touchPos.x + cosf(_pool->getUsedObject(i)->angle) * 90;
						_pool->getUsedObject(i)->y = _pool->getUsedObject(i)->touchPos.y - sinf(_pool->getUsedObject(i)->angle) * 30;
					}
					_pool->getUsedObject(i)->angle += 0.04f;

					break;
					
				case 5:case 7:case 9:case 11:
					 _pool->getUsedObject(i)->touchPos.x -= 13.0f;
					 _pool->getUsedObject(i)->touchPos.y = _slope2 * _pool->getUsedObject(i)->touchPos.x + _intercept2;

					if (_pool->getUsedObject(i)->id == 5)	// 아래 작은 오른쪽 대각선
					{
						_pool->getUsedObject(i)->x = _pool->getUsedObject(i)->touchPos.x + (+cosf(_pool->getUsedObject(i)->angle) * 30) *
							cosf(AXISANGLE/* -PI/10*/) + (-sinf(_pool->getUsedObject(i)->angle) * 90) * sinf(AXISANGLE/*-PI/10*/);
						_pool->getUsedObject(i)->y = _pool->getUsedObject(i)->touchPos.y + (-sinf(_pool->getUsedObject(i)->angle) * 90) *
							cosf(AXISANGLE/*- PI/10*/) - (+cosf(_pool->getUsedObject(i)->angle) * 30) *sinf(AXISANGLE/*-PI/10*/);
					}
					if (_pool->getUsedObject(i)->id == 7)	// 아래 작은 왼쪽 대각선
					{
						_pool->getUsedObject(i)->x = _pool->getUsedObject(i)->touchPos.x + (+cosf(_pool->getUsedObject(i)->angle) * 90)*
							cosf(AXISANGLE/*+PI/10*/) + (-sinf(_pool->getUsedObject(i)->angle) * 30) * sinf(AXISANGLE/*+PI/10*/);
						_pool->getUsedObject(i)->y = _pool->getUsedObject(i)->touchPos.y + (-sinf(_pool->getUsedObject(i)->angle) * 30) *
							cosf(AXISANGLE/*+PI/10*/) - (+cosf(_pool->getUsedObject(i)->angle) * 90) *sinf(AXISANGLE/*+PI/10*/);
					}
					if (_pool->getUsedObject(i)->id == 9)	// 아래 작은 세로
					{
						_pool->getUsedObject(i)->x = _pool->getUsedObject(i)->touchPos.x + (+cosf(_pool->getUsedObject(i)->angle) * 30);
						_pool->getUsedObject(i)->y = _pool->getUsedObject(i)->touchPos.y + (-sinf(_pool->getUsedObject(i)->angle) * 90);
					}
					
					if (_pool->getUsedObject(i)->id == 11)	// 아래 작은 가로
					{
						_pool->getUsedObject(i)->x = _pool->getUsedObject(i)->touchPos.x + cosf(_pool->getUsedObject(i)->angle) * 90;
						_pool->getUsedObject(i)->y = _pool->getUsedObject(i)->touchPos.y - sinf(_pool->getUsedObject(i)->angle) * 30;
					}
					_pool->getUsedObject(i)->angle += 0.04f;
					break;

				default:
					_pool->getUsedObject(i)->x += cosf(_pool->getUsedObject(i)->angle) * (_pool->getUsedObject(i)->speed - 35);
					_pool->getUsedObject(i)->y -= sinf(_pool->getUsedObject(i)->angle) * (_pool->getUsedObject(i)->speed - 35);
					break;
				}
			}
			else
			{
				switch (_pool->getUsedObject(i)->id)
				{
				case 4:case 6:case 8:case 10:
					_slope1 = (_target.y - _pool->getUsedObject(i)->touchPos.y) / (_target.x - _pool->getUsedObject(i)->touchPos.x);
					_intercept1 = _target.y - _slope1 * _target.x;
					break;
				case 5:case 7:case 9:case 11:
					_slope2 = (_target.y - _pool->getUsedObject(i)->touchPos.y) / (_target.x - _pool->getUsedObject(i)->touchPos.x);
					_intercept2 = _target.y - _slope2 * _target.x;
					break;
				}
				

				if (_pool->getUsedObject(i)->id == 0)	// 가로
				{
					_pool->getUsedObject(i)->x = _pool->getUsedObject(i)->touchPos.x + cosf(_pool->getUsedObject(i)->angle) * (_pool->getUsedObject(i)->speed + 120);
					_pool->getUsedObject(i)->y = _pool->getUsedObject(i)->touchPos.y - sinf(_pool->getUsedObject(i)->angle) * (_pool->getUsedObject(i)->speed);
				}
				if (_pool->getUsedObject(i)->id == 1)	// 세로
				{
					_pool->getUsedObject(i)->x = _pool->getUsedObject(i)->touchPos.x + cosf(_pool->getUsedObject(i)->angle) * (_pool->getUsedObject(i)->speed);
					_pool->getUsedObject(i)->y = _pool->getUsedObject(i)->touchPos.y - sinf(_pool->getUsedObject(i)->angle) * (_pool->getUsedObject(i)->speed + 130);
				}
				if (_pool->getUsedObject(i)->id == 2)	// 왼쪽 대각선
				{
					_pool->getUsedObject(i)->x = _pool->getUsedObject(i)->touchPos.x + (+cosf(_pool->getUsedObject(i)->angle) * 50)* 
						cosf(AXISANGLE) + (-sinf(_pool->getUsedObject(i)->angle) * 200) * sinf(AXISANGLE);
					_pool->getUsedObject(i)->y = _pool->getUsedObject(i)->touchPos.y + (-sinf(_pool->getUsedObject(i)->angle) * 200) * 
						cosf(AXISANGLE) - (+cosf(_pool->getUsedObject(i)->angle) * 50) *sinf(AXISANGLE);
				}
				if (_pool->getUsedObject(i)->id == 3)	// 오른쪽 대각선
				{
					_pool->getUsedObject(i)->x = _pool->getUsedObject(i)->touchPos.x + (+cosf(_pool->getUsedObject(i)->angle) * 200) * 
						cosf(AXISANGLE) + (-sinf(_pool->getUsedObject(i)->angle) * 50) * sinf(AXISANGLE);
					_pool->getUsedObject(i)->y = _pool->getUsedObject(i)->touchPos.y + (-sinf(_pool->getUsedObject(i)->angle) * 50) * 
						cosf(AXISANGLE) - (+cosf(_pool->getUsedObject(i)->angle) * 200) *sinf(AXISANGLE);
				}

				if (_pool->getUsedObject(i)->id == 4)	// 위에 작은 왼쪽 대각선
				{
					_pool->getUsedObject(i)->x = _pool->getUsedObject(i)->touchPos.x + (+cosf(_pool->getUsedObject(i)->angle) * 30) * 
						cosf(AXISANGLE/* -PI/10*/) + (-sinf(_pool->getUsedObject(i)->angle) * 90) * sinf(AXISANGLE/*-PI/10*/);
					_pool->getUsedObject(i)->y = _pool->getUsedObject(i)->touchPos.y + (-sinf(_pool->getUsedObject(i)->angle) * 90) * 
						cosf(AXISANGLE/*- PI/10*/) - (+cosf(_pool->getUsedObject(i)->angle) * 30) *sinf(AXISANGLE/*-PI/10*/);
				}
				if (_pool->getUsedObject(i)->id == 5)	// 아래 작은 오른쪽 대각선
				{
					_pool->getUsedObject(i)->x = _pool->getUsedObject(i)->touchPos.x + (+cosf(_pool->getUsedObject(i)->angle) * 30) *
						cosf(AXISANGLE/* -PI/10*/) + (-sinf(_pool->getUsedObject(i)->angle) * 90) * sinf(AXISANGLE/*-PI/10*/);
					_pool->getUsedObject(i)->y = _pool->getUsedObject(i)->touchPos.y + (-sinf(_pool->getUsedObject(i)->angle) * 90) *
						cosf(AXISANGLE/*- PI/10*/) - (+cosf(_pool->getUsedObject(i)->angle) * 30) *sinf(AXISANGLE/*-PI/10*/);
				}
				if (_pool->getUsedObject(i)->id == 6)	// 위에 작은 오른쪽 대각선
				{
					_pool->getUsedObject(i)->x = _pool->getUsedObject(i)->touchPos.x + (+cosf(_pool->getUsedObject(i)->angle) * 90)*  
						cosf(AXISANGLE/*+PI/10*/) + (-sinf(_pool->getUsedObject(i)->angle) * 30) * sinf(AXISANGLE/*+PI/10*/);
					_pool->getUsedObject(i)->y = _pool->getUsedObject(i)->touchPos.y + (-sinf(_pool->getUsedObject(i)->angle) * 30) * 
						cosf(AXISANGLE/*+PI/10*/) - (+cosf(_pool->getUsedObject(i)->angle) * 90) *sinf(AXISANGLE/*+PI/10*/);
				}
				if (_pool->getUsedObject(i)->id == 7)	// 아래 작은 왼쪽 대각선
				{
					_pool->getUsedObject(i)->x = _pool->getUsedObject(i)->touchPos.x + (+cosf(_pool->getUsedObject(i)->angle) * 90)*
						cosf(AXISANGLE/*+PI/10*/) + (-sinf(_pool->getUsedObject(i)->angle) * 30) * sinf(AXISANGLE/*+PI/10*/);
					_pool->getUsedObject(i)->y = _pool->getUsedObject(i)->touchPos.y + (-sinf(_pool->getUsedObject(i)->angle) * 30) *
						cosf(AXISANGLE/*+PI/10*/) - (+cosf(_pool->getUsedObject(i)->angle) * 90) *sinf(AXISANGLE/*+PI/10*/);
				}
				if (_pool->getUsedObject(i)->id == 8)	// 위에 작은 세로
				{
					_pool->getUsedObject(i)->x = _pool->getUsedObject(i)->touchPos.x + (+cosf(_pool->getUsedObject(i)->angle) * 30);
					_pool->getUsedObject(i)->y = _pool->getUsedObject(i)->touchPos.y + (-sinf(_pool->getUsedObject(i)->angle) * 90);
				}
				if (_pool->getUsedObject(i)->id == 9)	// 아래 작은 세로
				{
					_pool->getUsedObject(i)->x = _pool->getUsedObject(i)->touchPos.x + (+cosf(_pool->getUsedObject(i)->angle) * 30);
					_pool->getUsedObject(i)->y = _pool->getUsedObject(i)->touchPos.y + (-sinf(_pool->getUsedObject(i)->angle) * 90);
				}
				if (_pool->getUsedObject(i)->id == 10)	// 위에 작은 가로
				{
					_pool->getUsedObject(i)->x = _pool->getUsedObject(i)->touchPos.x + cosf(_pool->getUsedObject(i)->angle) * 90;
					_pool->getUsedObject(i)->y = _pool->getUsedObject(i)->touchPos.y - sinf(_pool->getUsedObject(i)->angle) * 30;
				}
				if (_pool->getUsedObject(i)->id == 11)	// 아래 작은 가로
				{
					_pool->getUsedObject(i)->x = _pool->getUsedObject(i)->touchPos.x + cosf(_pool->getUsedObject(i)->angle) * 90;
					_pool->getUsedObject(i)->y = _pool->getUsedObject(i)->touchPos.y - sinf(_pool->getUsedObject(i)->angle) * 30;
				}
					_pool->getUsedObject(i)->angle += 0.04f;
			}

			if (_pool->getUsedObject(i)->timer > 150) _isGo = true;
			break;
		case BULLET_MOVE_NONE:
			_pool->getUsedObject(i)->x += cosf(_pool->getUsedObject(i)->angle) * _pool->getUsedObject(i)->speed;
			_pool->getUsedObject(i)->y -= sinf(_pool->getUsedObject(i)->angle) * _pool->getUsedObject(i)->speed;
			break;
		default: break;
		}

		
		_pool->getUsedObject(i)->rc = RectMakeCenter(_pool->getUsedObject(i)->x, _pool->getUsedObject(i)->y, _img->getWidth(), _img->getHeight());

		//if (getDistance(_pool->getUsedObject(i).x, _pool->getUsedObject(i).y, _pool->getUsedObject(i).fireX, _pool->getUsedObject(i).fireY) > WINSIZEX - 10) _pool->colInsert(i);
		if (_pool->getUsedObject(i)->x > WINSIZEX || _pool->getUsedObject(i)->x + _img->getWidth() < 0 ||
			_pool->getUsedObject(i)->y > WINSIZEY || _pool->getUsedObject(i)->y + _img->getHeight() < 0) _pool->colInsert(i);
	}
}

void bullet::setAngle(float angle)
{
	if (!_pool->getUsedPoolSize()) return;
	for (int i = 0; i < _pool->getUsedPoolSize(); i++)
	{
		_pool->getUsedObject(i)->angle += angle;
	}
}

void bullet::setSpeed(float speed)
{
	if (!_pool->getUsedPoolSize()) return;
	for (int i = 0; i < _pool->getUsedPoolSize(); i++)
	{
		_pool->getUsedObject(i)->speed = speed;
	}
}

void bullet::setTouchPosition(POINTFLOAT pos)
{
	if (!_pool->getUsedPoolSize()) return;
	for (int i = 0; i < _pool->getUsedPoolSize(); i++)
	{
		_pool->getUsedObject(i)->touchPos.x = pos.x;
		_pool->getUsedObject(i)->touchPos.y = pos.y;
	}
}

