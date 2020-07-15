#pragma once
#include "gameNode.h"
#include "effect.h"
#include <vector>

class effectManager : public gameNode
{
private:
	vector<effect*>				_vEffect;
	vector<effect*>::iterator	_viEffect;

public:
	effectManager();
	~effectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void removeEffect(int num);
	void setEffect(const char* imgName, POINT pos, int frameSpeed);
};

