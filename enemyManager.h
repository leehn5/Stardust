#pragma once
#include "gameNode.h"
#include "itemDropEnemy.h"
#include "minion2.h"
#include "chainSaw.h"
#include "twoFire.h"
#include "enemyGreen.h"
#include "boss.h"
#include "bullets.h"
#include <vector>

class player;
class itemManager;
class effectManager;

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*>				vEnemy;
	typedef vector<enemy*>::iterator	viEnemy;

private:
	vEnemy								_vMinion;
	viEnemy								_viMinion;
	vector<boss*>						_vBoss;
	vector<boss*>::iterator				_viBoss;

	bullet*								_bullet;
	player*								_player;
	itemManager*						_itemMgr;
	effectManager*						_effectMgr;

	int									_enemyType;
	int									_enemyFrame;
	int									_gameFrame;
	int									_rndEnemyAppear;

public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//미니언 셋팅 함수
	void setMinion();
	void setBoss();

	//미니언 총알 발사 명령 함수
	void minionBulletFire();

	void removeMinion(int arrNum);
	void removeBoss(int arrNum);

	void collision();

	void linkedPlayer(player* player) { _player = player; }
	void linkedEffectManager(effectManager* effect) { _effectMgr = effect; }
	void linkedItemManager(itemManager* itemMgr) { _itemMgr = itemMgr; }

	void enemyToBeErase();

	vector<enemy*> getVMinion() { return _vMinion; }
	vector<boss*> getVBoss() { return _vBoss; }
	vector<enemy*>::iterator getViMinion() { return _viMinion; }
	vector<boss*>::iterator getViBoss() { return _viBoss; }
};

