#pragma once
#include "gameNode.h"
#include <vector>
#include <queue>

#define AXISANGLE PI/4

enum BULLET_MOVE_TYPE
{
	BULLET_MOVE_NORMAL,
	BULLET_MOVE_NORMAL_ROTATION,
	BULLET_MOVE_ROTATION,
	BULLET_MOVE_ROTATION2,
	BULLET_MOVE_SATELLITE,
	BULLET_MOVE_NONE,
};

struct tagBullet
{
	RECT rc;
	float x, y;
	float speed;
	float angle;
	int timer;
	int id;
	POINTFLOAT touchPos;
	BULLET_MOVE_TYPE moveType;
};

class ObjectPool
{
private:
	//tagBullet _obj;
	//priority_queue <tagBullet> *_pool;
	queue <tagBullet*> _pool;
	vector<tagBullet*> _usedPool;

public:
	ObjectPool() {};
	~ObjectPool() {};

	void CreatePool(int size);
	void InssertQueue();
	void colInsert(int num);
	void setUsedObject();

	// 처음에 설정한 오브젝트, 디폴트 오브젝트 가져오기
	inline tagBullet* getObject() { return _pool.front(); }

	// usedPool 실제로 날아가는 아이의 정보를 가져온다
	inline tagBullet* getUsedObject(int num) { return _usedPool[num]; }

	// 실제 pool의 사이즈
	// fire 할 때 이 녀석의 사이즈만큼만 돌게 해줘야 함
	inline int getSize() { return _pool.size(); }

	// for문 돌릴 때는 이 아이를 써야한다
	// render에서 돌릴 때 이 아이의 사이즈가 0일 때 돌면 안 되니까 이거 막아야 함 (★중요)
	inline int getUsedPoolSize() { return _usedPool.size(); }
};

class bullet : public gameNode
{
private:
	image* _img;
	ObjectPool* _pool;

	//BULLET_MOVE_TYPE _moveType;

	float _angle;
	float _slope1, _slope2;
	float _intercept1, _intercept2;

	POINTFLOAT _target;

	bool _isGo;

public:
	bullet() {};
	~bullet() {};

	HRESULT init(const char* imageName, int size);
	void release();
	void update();
	void render();
	void rotateRender();

	//void bulletFire(float x, float y, float angle, float speed, BULLET_MOVE_TYPE moveType = BULLET_MOVE_NORMAL);
	void bulletFire(int id, float x, float y, float angle, float speed, BULLET_MOVE_TYPE moveType = BULLET_MOVE_NORMAL, bool isGo = true);
	void bulletFire(float x, float y, float angle, float speed, BULLET_MOVE_TYPE moveType = BULLET_MOVE_NORMAL, bool isGo = true);
	void bulletFire(float x, float y, float angle, float speed, POINTFLOAT pos, BULLET_MOVE_TYPE moveType = BULLET_MOVE_NORMAL, bool isGo = true);
	void bulletFire(int id, float x, float y, float angle, float speed, POINTFLOAT pos, BULLET_MOVE_TYPE moveType = BULLET_MOVE_NORMAL, bool isGo = true);

	void bulletMove();

	void setBulletImage(const char* imageName) { _img = IMAGEMANAGER->findImage(imageName); }
	void setAngle(float angle);
	void setSpeed(float speed);
	void setTarget(POINTFLOAT pos) { _target = pos; }
	void setIsGo(bool isGo) { _isGo = isGo; }
	void setTouchPosition(POINTFLOAT pos);
	bool getIsGo() { return _isGo; }

	ObjectPool* getBullet() { return _pool; }

};