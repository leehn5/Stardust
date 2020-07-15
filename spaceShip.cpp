#include "stdafx.h"
#include "spaceShip.h"
#include "enemyManager.h"

spaceShip::spaceShip()
{
}


spaceShip::~spaceShip()
{
}

HRESULT spaceShip::init()
{
	_ship = IMAGEMANAGER->addImage("�÷��̾�", "rocket.bmp", 52, 64, true, RGB(255, 0, 255));
	_ship->setX(WINSIZEX / 2);
	_ship->setY(WINSIZEY / 2 + 200);
	_ship->setRotationAngle(PI);
	_ship->setAlpha(150);

	//_missile = new missile;
	//_missile->init(30, 400);

	//_boy = new littleBoy;
	//_boy->init(30, 800);

	_hpBar = new progressBar;
	_hpBar->init(_ship->getX(), _ship->getY() - 10, _ship->getWidth(), 10);
	_currentHP = _maxHP = 100;



	return S_OK;
}

void spaceShip::release()
{
}

void spaceShip::update()
{
	//���� �̵�
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _ship->getX() > 0)
	{
		_ship->setX(_ship->getX() - 5);
	}

	//������ �̵�
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _ship->getX() + _ship->getWidth() < WINSIZEX)
	{
		_ship->setX(_ship->getX() + 5);
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _ship->getY() > 0)
	{
		_ship->setY(_ship->getY() - 5);
		

		
		
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _ship->getY() + _ship->getHeight() < WINSIZEY)
	{
		_ship->setY(_ship->getY() + 5);

		
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//_missile->fire(_ship->getCenterX(), _ship->getY() - 20);
		_ship->setAlpha(_ship->getAlpha() - 100);
		_ship->setRotationAngle(_ship->getRotationAngle() - PI/2);

	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		//_boy->fire(_ship->getCenterX(), _ship->getY() - 10);
	}

	//_missile->update();
	//_boy->update();

	//76, 77, 78��° �ٱ����ؼ� ���α׷��� ���� ��ġ�� ���ּ��� �����ش�
	_hpBar->setX(_ship->getX());
	_hpBar->setY(_ship->getY() - 20);
	_hpBar->update();

	_hpBar->setGauge(_currentHP, _maxHP);



	collision();

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		char temp[128];
		vector<string> vStr;

		vStr.push_back(itoa(_currentHP, temp, 10));
		vStr.push_back(itoa(_maxHP, temp, 10));
		vStr.push_back(itoa(_ship->getX(), temp, 10));
		vStr.push_back(itoa(_ship->getY(), temp, 10));

		TXTDATA->txtSave("���̺��׽�Ʈ.txt", vStr);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		vector<string> vStr;

		vStr = TXTDATA->txtLoad("���̺��׽�Ʈ.txt");

		_currentHP = (atoi(vStr[0].c_str()));
		_maxHP = (atoi(vStr[1].c_str()));
		_ship->setX(atoi(vStr[2].c_str()));
		_ship->setY(atoi(vStr[3].c_str()));
	}



}

void spaceShip::render()
{
	//_ship->render(getMemDC(), _ship->getX(), _ship->getY());
	//_ship->alphaRender(getMemDC(), _ship->getX(), _ship->getY(), _ship->getAlpha());

	//_ship->rotateRender(getMemDC(), _ship->getCenterX(), _ship->getCenterY(), _ship->getRotationAngle());

	IMAGEMANAGER->findImage("�÷��̾�")->alphaRotateRender(getMemDC(), _ship->getCenterX(), _ship->getCenterY(), _ship->getRotationAngle(), _ship->getAlpha());

	char buffer[128];
	sprintf_s(buffer, "%d", int(_ship->getAlpha()));
	TextOut(getMemDC(), 50, 100, buffer, strlen(buffer));


	//_missile->render();
	//_boy->render();
	_hpBar->render();
}

void spaceShip::collision()
{
	//for (int i = 0; i < _em->getVMinion().size(); i++)
	//{
	//	for (int j = 0; j < _boy->getVBoy().size(); j++)
	//	{
	//		RECT temp;
	//		if (IntersectRect(&temp, &_boy->getVBoy()[j].rc, &_em->getVMinion()[i]->getRect()))
	//		{
	//			_em->removeMinion(i);
	//			_boy->removeBoy(j);
	//			break;
	//		}
	//	}
	//}
}

void spaceShip::hitDamage(float damage)
{
	_currentHP -= damage;
}
