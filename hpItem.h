#pragma once
#include "item.h"

class hpItem : public item
{
public:
	hpItem() {};
	~hpItem() {};

	virtual HRESULT init(POINT pos);
	virtual void update();
};

