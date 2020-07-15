#pragma once
#include "gameNode.h"

#define SCORE_SPACE 10

class player;

class UI : public gameNode
{
private:
	image* _imgHpForm;
	image* _imgHp;
	image* _imgScore[SCORE_SPACE];

	player* _player;

	RECT _rc[6];

	int _currentFrameX;

public:
	UI();
	~UI();

	virtual HRESULT init();
	virtual HRESULT init(player* player);
	virtual void release();
	virtual void update();
	virtual void render();

	void linkedPlayer(player* player) { _player = player; }
};

