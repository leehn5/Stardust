#pragma once
#include "object.h"

class effect : public object
{
private:
	int _frameSpeed;

public:
	effect() {};
	~effect() {};

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT pos, int frameSpeed);
	virtual void release();
	virtual void update();
	virtual void render();

	bool isAnyEnd();
};

