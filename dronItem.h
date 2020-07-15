#pragma once
#include "item.h"

class dronItem : public item
{
public:
	dronItem() {};
	~dronItem() {};

	virtual HRESULT init(POINT pos);
	virtual void update();
};

