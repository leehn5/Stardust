#pragma once
#include "gameNode.h"

class gameExplanation : public gameNode
{
	bool	_isStart;
	bool	_isHowTO1;
	bool	_isHowTO2;

	int		_timer;
	int		_alpha;

public:
	gameExplanation();
	~gameExplanation();

	HRESULT init();
	void release();
	void update();
	void render();

	bool getIsStart() { return _isStart; }
};

