#pragma once
#include "singletonBase.h"
#include "image.h"
#include <map>

class imageManager : public singletonBase<imageManager>
{
private:
	typedef map<string, image*>				mapImageList;
	typedef map<string, image*>::iterator	mapImageIter;

private:
	mapImageList _mImageList;

public:
	imageManager();
	~imageManager();

	HRESULT init();
	void release();

	image* addImage(string strKey, int width, int height);
	image* addImage(string strKey, const char* fileName, int width, int height, bool trans = FALSE, COLORREF transColor = RGB(255, 0, 255));

	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans = FALSE, COLORREF transColor = RGB(255, 0, 255));
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans = FALSE, COLORREF transColor = RGB(255, 0, 255));

	//이미지 찾는 함수
	image* findImage(string strKey);

	//이미지 지워주는 함쑤
	BOOL deleteImage(string strKey);

	BOOL deleteAll();

	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void frameRender(string strKey,HDC hdc, int destX, int destY);
	void frameRender(string strKey,HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void alphaRender(string strKey,HDC hdc, BYTE alpha);
	void alphaRender(string strKey,HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey,HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void alphaFrameRender(string strKey,HDC hdc, int destX, int destY, BYTE alpha);
	void alphaFrameRender(string strKey,HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);


	void rotateRender(string strKey, HDC hdc, float centerX, float centerY, float angle);
	void alphaRotateRender(string strKey, HDC hdc, float centerX, float centerY, float angle, BYTE alpha);
	void rotateFrameRender(string strKey, HDC hdc, float centerX, float centerY, float angle);
	void rotateFrameRender(string strKey, HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle);
	void alphaRotateFrameRender(string strKey, HDC hdc, float centerX, float centerY, float angle, BYTE alpha);
	void alphaRotateFrameRender(string strKey, HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle, BYTE alpha);
	
	void loopRender(string strKey,HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);


};

