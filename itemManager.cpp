#include "stdafx.h"
#include "itemManager.h"
#include "player.h"
#include "dronManager.h"

HRESULT itemManager::init()
{
	return S_OK;
}

void itemManager::release()
{
}

void itemManager::update()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		(*_viItem)->update();
	}

	itemToBeErase();
	collision();
}

void itemManager::render()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		(*_viItem)->render();
	}
}

void itemManager::setItem(POINT pos)
{
	_itemType = RND->getInt(ITEM_END);
	//_itemType = ITEM_DRON;

	item* it;

	switch (_itemType)
	{
	case ITEM_HP:
	{
		it = new hpItem;
		it->init(pos);
	}
		break;
	case ITEM_POWER:
	{
		it = new powerItem;
		it->init(pos);
	}
		break;
	case ITEM_DRON:
	{
		it = new dronItem;
		it->init(pos);
	}
		break;
	default: break;
	}
	
	_vItem.push_back(it);
}

void itemManager::removeItem(int num)
{
	_vItem.erase(_vItem.begin() + num);
}

void itemManager::itemToBeErase()
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		if (_vItem[i]->getRect().right < 0) removeItem(i);
	}
}

void itemManager::collision()
{
	RECT temp;
	for (int i = 0; i < _vItem.size(); i++)
	{
		if (IntersectRect(&temp, &_vItem[i]->getRect(), &_player->getRect()))
		{
			if (_vItem[i]->getItemType() == ITEM_HP)
			{
				_player->healHP(1);
				_player->setScore(10);
			}
			else if (_vItem[i]->getItemType() == ITEM_POWER)
			{
				_player->setBulletType(1);
				_player->setScore(15);
			}
			else if (_vItem[i]->getItemType() == ITEM_DRON)
			{
				_player->getDronManager()->setDron();
				_player->setScore(20);
			}
			removeItem(i);
			break;
		}
	}
}
