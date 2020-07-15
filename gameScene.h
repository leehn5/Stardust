#pragma once
#include "gameNode.h"
#include "player.h"
#include "UI.h"
#include "enemyManager.h"
#include "effectManager.h"
#include "itemManager.h"
#include "dronManager.h"
#include "gameExplanation.h"

class gameScene : public gameNode
{
private:
	gameExplanation*	_ge;
	player*				_player;
	enemyManager*		_em;
	effectManager*		_effect;
	itemManager*		_item;
	dronManager*		_dron;
	UI*					_ui;

	int					_loopCount;

public:
	gameScene();
	~gameScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

