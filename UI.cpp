#include "stdafx.h"
#include "UI.h"
#include "player.h"

UI::UI()
{
}

UI::~UI()
{
}

HRESULT UI::init()
{

	return S_OK;
}

HRESULT UI::init(player * player)
{
	_imgHpForm = IMAGEMANAGER->findImage("playerHP");
	
	_currentFrameX = 0;
	
	_imgHp = IMAGEMANAGER->findImage("hpState");
	
	for (int i = 0; i < player->getCurrentHP(); i++)
	{
		_rc[i] = RectMake(28 + i * 16, 27, _imgHp->getFrameWidth(), _imgHp->getFrameHeight());
	}

	char str[128];
	for (int i = 0; i < SCORE_SPACE; i++)
	{
		sprintf_s(str, "%d", i);
		_imgScore[i] = IMAGEMANAGER->findImage(str);
	}

	return S_OK;
}

void UI::release()
{
	SAFE_DELETE(_imgHpForm);
	SAFE_DELETE(_imgHp);
}

void UI::update()
{
	if (_player->getCurrentHP() > 4) _currentFrameX = 0;
	else if (_player->getCurrentHP() > 2) _currentFrameX = 1;
	else if (_player->getCurrentHP() > 0) _currentFrameX = 2;

	_imgHp->setFrameX(_currentFrameX);
}

void UI::render()
{
	_imgHpForm->render(getMemDC(), 20, 20);
	
	for (int i = 0; i < _player->getCurrentHP(); i++)
	{
		_imgHp->frameRender(getMemDC(), _rc[i].left, _rc[i].top);
	}

	for (int i = 0; i < SCORE_SPACE; i++)
	{
		_imgScore[(_player->getScore() / (int)pow(10, i)) % 10]->render(getMemDC(), 202 - i * 20, 70);
	}

	//char str[128];
	//sprintf_s(str, "%d", _player->getScore());
	//TextOut(getMemDC(), 25, 70, str, strlen(str));
}
