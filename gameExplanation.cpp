#include "stdafx.h"
#include "gameExplanation.h"

gameExplanation::gameExplanation()
{
}

gameExplanation::~gameExplanation()
{
}

HRESULT gameExplanation::init()
{
	gameNode::init(true);

	_isStart = _isHowTO1 = _isHowTO2 = false;
	_timer = _alpha = 0;

	return S_OK;
}

void gameExplanation::release()
{
	gameNode::release();
}

void gameExplanation::update()
{
	gameNode::update();

	if (_alpha < 254) _alpha += 2;
	IMAGEMANAGER->findImage("title")->setAlpha(_alpha);

	if (KEYMANAGER->isOnceKeyDown('Z')) _isStart = true;

	if (!_isHowTO1 && KEYMANAGER->isOnceKeyDown(VK_RETURN) && _alpha > 252) _isHowTO1 = true;
	if (_isHowTO1 && !_isHowTO2 &&  KEYMANAGER->isOnceKeyDown(VK_RETURN)) _isHowTO2 = true;
	if (_isHowTO1 && _isHowTO2 &&  KEYMANAGER->isOnceKeyDown(VK_RETURN)) _isStart = true;
}

void gameExplanation::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	IMAGEMANAGER->findImage("title")->alphaRender(getMemDC(), _alpha);
	if (_isHowTO1)
	{
		IMAGEMANAGER->findImage("howTo1")->render(getMemDC());
		IMAGEMANAGER->findImage("round")->render(getMemDC());
	}
	if (_isHowTO2)
	{
		IMAGEMANAGER->findImage("howTo2")->render(getMemDC());
		IMAGEMANAGER->findImage("round")->render(getMemDC());
	}

	_backBuffer->render(getHDC(), 0, 0);
}
