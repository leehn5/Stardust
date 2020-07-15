#pragma once
#include "gameNode.h"
#include "item.h"
#include "hpItem.h"
#include "powerItem.h"
#include "dronItem.h"
#include <vector>

class player;

class itemManager : public gameNode
{
private:
	vector<item*>			_vItem;
	vector<item*>::iterator	_viItem;

	player* _player;

	int _itemType;

public:
	itemManager() {};
	~itemManager() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void setItem(POINT pos);

	void removeItem(int num);
	void itemToBeErase();

	void collision();

	void linkedPlayer(player* player) { _player = player; }

	vector<item*> getvItem() { return _vItem; }
};

