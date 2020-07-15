#pragma once
#include "object.h"

//#define DRON_MAX 4

enum DRON_TYPE
{
	DRON_NORMAL,
	DRON_SIX_DIRECTION,
	DRON_NONE,
};

//struct tagDron
//{
//	float x;
//	float y;
//	bool isOn;
//	DRON_TYPE type;
//};

//class dron : public object
//{
//private:
//	image*		_img;
//
//	tagDron		_dron[DRON_MAX];
//	DRON_TYPE	_type;
//
//	int			_fireCount;
//	POINTFLOAT	_target;
//
//public:
//	dron() {};
//	~dron() {};
//
//	virtual HRESULT init();
//	virtual void release();
//	virtual void update();
//	virtual void render();
//
//	void move();
//	void turnOnDron();
//	void turnOffAllDron();
//
//	void fire();
//
//	void setTargetPosition(POINTFLOAT pos) { _target = pos; }
//
//	bool isFireCount();
//};


class dron : public object
{
private:
	DRON_TYPE	_type;

	POINTFLOAT	_target;

	bool		_isOn;

public:
	dron() {};
	~dron() {};

	virtual HRESULT init();
	virtual HRESULT init(DRON_TYPE type);
	virtual void release();
	virtual void update();
	virtual void render();

	void setTargetPosition(POINTFLOAT pos) { _target = pos; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

	DRON_TYPE getDronType() { return _type; }
};