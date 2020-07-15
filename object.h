#pragma once
#include "gameNode.h"

class object : public gameNode
{
protected:
	float _x, _y;
	float _speed;
	float _bulletSpeed;

	int _currentHP;
	int _maxHP;

	int _currentFrameX;
	int _currentFrameY;

	int _frameCount;

	int _alpha;
	int _alphaTimer;

	float _moveTime;
	float _angle;

	RECT _rc;
	image* _img;

public:
	object();
	~object();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void frameCount(int time);

	virtual void hitProcessing(int atk, int timer = 0);
	void alphaBlending();

	void healHP(int value);
	void hitDamage(int atk);

	inline int getCurrentHP() { return _currentHP; }
	inline RECT getRect() { return _rc; }
	inline POINTFLOAT getPosition() { return { _x, _y }; }
	inline image* getImage() { return _img; }
	inline POINT getCenterRect() { return PointMake(_rc.left + (_rc.right - _rc.left) / 2, _rc.top + (_rc.bottom - _rc.top) / 2); }
	inline POINT getCenterPosition() { return PointMake(_rc.left + (_rc.right - _rc.left) / 2, _rc.top + (_rc.bottom - _rc.top) / 2); }
	inline POINTFLOAT getFloatCenterRect() { return PointFloatMake(_rc.left + _img->getFrameWidth() / 2, _rc.top + _img->getFrameHeight() / 2); }
	inline float setAngle(float angle) { return _angle = angle; }

	bool isDead();
};