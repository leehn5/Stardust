#pragma once
#include "object.h"

enum ITEM_TYPE
{
	ITEM_HP,
	ITEM_POWER,
	ITEM_DRON,
	ITEM_END,
};

class item : public object
{
protected:
	ITEM_TYPE _itemType;

public:
	item() {};
	~item() {};

	virtual HRESULT init();
	virtual HRESULT init(POINT pos);
	virtual void release();
	virtual void update();
	virtual void render();

	void move();
	ITEM_TYPE getItemType() { return _itemType; }
};

