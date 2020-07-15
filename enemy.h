#pragma once
#include "object.h"

enum ENEMY_TYPE
{
	ENEMY_ITEM_DROP,
	ENEMY_MINION1,
	ENEMY_CHAIN_SAW,
	ENEMY_TWO_FIRE,
	ENEMY_GREEN,
	ENEMY_END,
};

class enemy : public object
{
protected:
	int _fireCount;			//ÃÑ¾Ë ¹ß»ç¿ë
	int _rndFireCount;		//·£´ýÇÏ°Ô ½ò º¯¼ö
	int _dir;

	ENEMY_TYPE _enemyType;

public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINTFLOAT pos);
	virtual HRESULT init(const char* imageName, POINTFLOAT pos, ENEMY_TYPE type, int dir = 1);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void hitProcessing(int atk, int timer = 0);

	void move();
	virtual void draw();

	ENEMY_TYPE getEnemyType() { return _enemyType; }
	bool bulletCountFire();

};

