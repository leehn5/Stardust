#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(const char * imageName, POINTFLOAT pos)
{
	_x = pos.x;
	_y = pos.y;

	_img = IMAGEMANAGER->findImage(imageName);
	_rndFireCount = RND->getFromIntTo(1, 300);

	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_speed = 2.0f;

	_frameCount = _currentFrameX = 0;

	_alpha = 255;

	_moveTime = 0;

	return S_OK;
}

HRESULT enemy::init(const char * imageName, POINTFLOAT pos, ENEMY_TYPE type, int dir)
{
	_x = pos.x;
	_y = pos.y;

	_img = IMAGEMANAGER->findImage(imageName);
	_rndFireCount = RND->getFromIntTo(1, 300);

	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_speed = 2.5f;

	_frameCount = _currentFrameX = 0;

	_enemyType = type;

	_alpha = 255;

	_moveTime = 0;

	_angle = PI;

	_dir = dir;

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	move();
	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void enemy::render()
{
	draw();
}

void enemy::hitProcessing(int atk, int timer)
{
	hitDamage(atk);
}

void enemy::move()
{
}

void enemy::draw()
{
	//Rectangle(getMemDC(), _rc);
	_img->alphaFrameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY, _alpha);
}

bool enemy::bulletCountFire()
{
	_fireCount++;

	if (_fireCount % _rndFireCount == 0)
	{
		_fireCount = 0;
		//_rndFireCount = RND->getFromIntTo(1, 1000);
		_rndFireCount = RND->getFromIntTo(1, 500);

		return true;
	}

	return false;
}
