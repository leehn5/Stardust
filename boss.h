#pragma once
#include "object.h"
#include "bullets.h"

class player;
class effectManager;

enum BOSS_PATTERN
{
	PATTERN_NORMAL_FIRE,
	PATTERN_ROTATE_FIRE,
	PATTERN_ROTATE_FIRE2,
	PATTERN_SATELLITE_FIRE,
	PATTERN_NONE,
};

class boss : public object
{
private:
	player*			_player;
	bullet*			_bullet;
	effectManager*	_ef;

	float			_bulletAngle;
	float			_bulletAngle2;
	float			_bulletTimer;
	float			_bulletMoveTime;

	int				_fireTime;
	int				_fireCount;
	int				_bossFire;
	int				_pattern;

	bool			_isFire;
	bool			_isHitOk;

public:
	boss();
	~boss();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName);
	virtual void release();
	virtual void update();
	virtual void render();

	void move();
	void collision();
	void linkedPlayer(player* player) { _player = player; }
	void linkedEffect(effectManager* effect) { _ef = effect; }

	bool countFire(int time, int count);
	bool fire();
	bool getIsHitOk() { return _isHitOk; }

	virtual void hitProcessing(int atk, int timer = 0) { if (_isHitOk) hitDamage(atk); }
};

