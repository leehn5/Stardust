#include "stdafx.h"
#include "gameScene.h"

gameScene::gameScene()
{
}

gameScene::~gameScene()
{
}

HRESULT gameScene::init()
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("background", "bg.bmp", 13500, 900);
	IMAGEMANAGER->addImage("0", "0.bmp", 15, 23, true);
	IMAGEMANAGER->addImage("1", "1.bmp", 15, 23, true);
	IMAGEMANAGER->addImage("2", "2.bmp", 15, 23, true);
	IMAGEMANAGER->addImage("3", "3.bmp", 15, 23, true);
	IMAGEMANAGER->addImage("4", "4.bmp", 15, 23, true);
	IMAGEMANAGER->addImage("5", "5.bmp", 15, 23, true);
	IMAGEMANAGER->addImage("6", "6.bmp", 15, 23, true);
	IMAGEMANAGER->addImage("7", "7.bmp", 15, 23, true);
	IMAGEMANAGER->addImage("8", "8.bmp", 15, 23, true);
	IMAGEMANAGER->addImage("9", "9.bmp", 15, 23, true);
	IMAGEMANAGER->addImage("playerBullet", "playerBullet3.bmp", 18, 18, true);
	IMAGEMANAGER->addImage("playerBullet2", "playerBullet2.bmp", 16, 15, true);
	IMAGEMANAGER->addImage("enemyBullet", "enemyBullet.bmp", 16, 16, true);
	IMAGEMANAGER->addImage("bossBullet", "bossBullet.bmp", 24, 24, true);
	IMAGEMANAGER->addImage("dronBullet", "droneBullet.bmp", 13, 8, true);
	IMAGEMANAGER->addImage("dronBullet2", "droneBullet2.bmp", 13, 8, true);
	//IMAGEMANAGER->addImage("playerBullet", "blue_bullet.bmp", 18, 20, true);
	IMAGEMANAGER->addImage("playerHP", "hpForm.bmp", 114, 32, true);
	IMAGEMANAGER->addImage("textSpace", "TextSpace.bmp", 1600, 900);
	IMAGEMANAGER->addImage("title", "TITLE.bmp", 1600, 900);
	IMAGEMANAGER->addImage("howTo1", "HowTo1.bmp", 1600, 900);
	IMAGEMANAGER->addImage("howTo2", "HowTo2.bmp", 1600, 900);
	IMAGEMANAGER->addImage("round", "round.bmp", 1600, 900, true);
	IMAGEMANAGER->addFrameImage("player", "player.bmp", 420, 38, 6, 1, true);
	IMAGEMANAGER->addFrameImage("hpState", "hpState.bmp", 39, 18, 3, 1);
	IMAGEMANAGER->addFrameImage("smallEffect", "smallEffect.bmp", 264, 22, 12, 1, true);
	IMAGEMANAGER->addFrameImage("enemyDeadEffect", "explosion.bmp", 2080, 103, 20, 1, true);
	IMAGEMANAGER->addFrameImage("itemEnemyEffect", "explosion2.bmp", 1764, 105, 18, 1, true);
	IMAGEMANAGER->addFrameImage("chainDeadEffect", "explosion3.bmp", 650, 50, 13, 1, true);
	IMAGEMANAGER->addFrameImage("playerDeadEffect", "explosion4.bmp", 2037, 112, 21, 1, true);
	IMAGEMANAGER->addFrameImage("itemDropEnemy", "AnimCargoV2.bmp", 1680, 51, 12, 1, true);
	IMAGEMANAGER->addFrameImage("hpItem", "HP.bmp", 680, 21, 20, 1, true);
	IMAGEMANAGER->addFrameImage("powerItem", "power.bmp", 300, 27, 10, 1, true);
	IMAGEMANAGER->addFrameImage("dronItem", "dronItem.bmp", 828, 46, 18, 1, true);
	IMAGEMANAGER->addFrameImage("enemy1", "enemy1.bmp", 640, 58, 8, 1, true);
	IMAGEMANAGER->addFrameImage("enemy_chainSaw", "enemy2.bmp", 540, 25, 12, 1, true);
	IMAGEMANAGER->addFrameImage("enemy_twoFire", "twoFireEnemy.bmp", 1128, 59, 12, 1, true);
	IMAGEMANAGER->addFrameImage("enemy_green", "minion2.bmp", 372, 41, 6, 1, true);
	IMAGEMANAGER->addFrameImage("boss", "boss.bmp", 6336, 127, 24, 1, true);
	IMAGEMANAGER->addFrameImage("dron", "dron.bmp", 210, 26, 7, 1, true);

	_ge = new gameExplanation;
	_ge->init();

	_player = new player;
	_player->init("player");

	_em = new enemyManager;
	_em->init();

	_effect = new effectManager;
	_effect->init();

	_item = new itemManager;
	_item->init();

	_ui = new UI;
	_ui->init(_player);

	_dron = new dronManager;
	_dron->init();

	_loopCount = 0;

	_player->linkedEnemyManager(_em);
	_player->linkedEffectManager(_effect);
	_player->linkedDronManager(_dron);

	_em->linkedPlayer(_player);
	_em->linkedEffectManager(_effect);
	_em->linkedItemManager(_item);

	_item->linkedPlayer(_player);

	_dron->linkedEnemyManager(_em);
	_dron->linkedEffectManager(_effect);

	_ui->linkedPlayer(_player);

	return S_OK;
}

void gameScene::release()
{
	gameNode::release();

	SAFE_DELETE(_ge);
	SAFE_DELETE(_player);
	SAFE_DELETE(_em);
	SAFE_DELETE(_effect);
	SAFE_DELETE(_item);
	SAFE_DELETE(_dron);
	SAFE_DELETE(_ui);
}

void gameScene::update()
{
	gameNode::update();

	_ge->update();

	if (_ge->getIsStart())
	{
		_player->update();
		_em->update();
		_effect->update();
		_item->update();
		_dron->update();
		_ui->update();

		_loopCount += 1;
	}

	if (_player->getIsDead()) this->init();
}

void gameScene::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	if (_ge->getIsStart())
	{
		IMAGEMANAGER->findImage("background")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _loopCount, 50);
		_player->render();
		_em->render();
		_effect->render();
		_item->render();
		_dron->render();
		_ui->render();
	}
	else _ge->render();

	_backBuffer->render(getHDC(), 0, 0);
}
