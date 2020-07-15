#pragma once
#include "item.h"

class powerItem : public item
{
public:
	powerItem() {};
	~powerItem() {};

	virtual HRESULT init(POINT pos);
	virtual void update();
};

