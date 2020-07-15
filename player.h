#pragma once
#include "object.h"
#include "bullets.h"

class enemyManager;
class effectManager;
class dronManager;

enum PLAYER_BULLET_TYPE
{
	BULLET_NORMAL,
	BULLET_THREE,
	BULLET_FIVE,
	BULLET_END,
};

class player : public object
{
private:
	bullet*				_bullet;
	bullet*				_bullet2;
	enemyManager*		_em;
	effectManager*		_effect;
	dronManager*		_dronMgr;

	int					_bulletType;
	int					_score;
	int					_deadTimer;

	float				_bulletAngle;

	bool				_isDead;

public:
	player();
	~player();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void hitProcessing(int atk, int timer = 0);

	void keycontrol();
	void collision();

	void setBulletType(int value);
	void setScore(int value) { _score += value; }
	int getScore() { return _score; }
	bool getIsDead() { return _isDead; }

	enemyManager* getEnemyManager() { return _em; }
	dronManager* getDronManager() { return _dronMgr; }

	void linkedEnemyManager(enemyManager* em) { _em = em; }
	void linkedEffectManager(effectManager* effect) { _effect = effect; }
	void linkedDronManager(dronManager* dron) { _dronMgr = dron; }
};

