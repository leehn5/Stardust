#pragma once
#include "gameNode.h"
#include "dron.h"
#include "bullets.h"
#include <vector>

class enemyManager;
class effectManager;

class dronManager : public gameNode
{
private:
	vector<dron*>				_vDron;
	vector<dron*>::iterator		_viDron;

	bullet*						_bullet;
	bullet*						_bullet2;

	enemyManager*				_em;
	effectManager*				_effect;

	int							_fireCount;

	POINTFLOAT					_targetPos;

public:
	dronManager();
	~dronManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void dronFire();
	void dronMove();

	void setDron();
	void setTargetPosition(POINTFLOAT pos) { _targetPos = pos; }

	void collision();
	void removeAll();

	bool isFireCount();
	
	bullet* getBullet() { return _bullet; }
	bullet* getBullet2() { return _bullet2; }

	void linkedEnemyManager(enemyManager* em) { _em = em; }
	void linkedEffectManager(effectManager* effect) { _effect = effect; }

	vector<dron*> getVDron() { return _vDron; }
};

