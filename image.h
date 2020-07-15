#pragma once

//=========================================
// ## 2019.11.15 ## Image ##
//=========================================

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,
		LOAD_FILE,
		LOAD_EMPTY,
		LOAD_END
	};


	typedef struct tagImageInfo
	{
		DWORD resID;
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float x;			//이미지 뿌려질 곳의 X(left)
		float y;			//이미지 뿌려질 곳의 Y(top)
		int width;			//이미지 전체 가로크기
		int height;			//이미지 전체 세로크기
		int currentFrameX;	//현재 프레임 가로번호 (X열)
		int currentFrameY;	//현재 프레임 세로번호 (Y열)
		int maxFrameX;		//최대 프레임 번호 가로
		int maxFrameY;		//최대 프레임 번호 세로
		int frameWidth;		//한 프레임의 가로크기
		int frameHeight;	//한 프레임의 세로크기

		bool isAlpha;		//알파 렌더 해야하나 
		BYTE alpha;			//알파값 
		BYTE loadType;

		bool isRotate;		//회전 해야하나 
		float rotationAngle;//회전 각도 


		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			rotationAngle = 0;
			alpha = 255;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;
private:
	LPIMAGE_INFO	_imageInfo;
	CHAR*			_fileName;
	BOOL			_trans;
	COLORREF		_transColor;

	BLENDFUNCTION _blendFunc;	//알파블렌드 관련 함수들
	LPIMAGE_INFO  _blendImage;	//알파블렌드 처리할 이미지

	
	LPIMAGE_INFO _rotateImage;	//회전 처리할 이미지 
public:
	image();
	~image();

	HRESULT init(int width, int height);
	HRESULT init(const DWORD resID, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = FALSE);
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	void release();

	void setTransColor(BOOL trans, COLORREF transColor);

	//렌더함수 (뿌려질 DC)
	void render(HDC hdc);
	//렌더함수 (뿌려질DC, 뿌릴좌표(left), 뿌릴좌표(top)
	void render(HDC hdc, int destX, int destY);
	//렌더함수 뿌려질DC, 뿌릴좌표X(left),뿌릴좌표Y(top), 잘라올곳X(left), 잘라올곳Y(top), 잘라올 가로크기, 잘라올 세로크기
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//이미지 프레임 렌더(뿌려질DC, 뿌려질left,  뿌려질top)
	void frameRender(HDC hdc, int destX, int destY);
	//이미지 프레임 렌더(뿌려질DC, 뿌려질left, 뿌려질top, 프레임X번호, 프레임Y번호
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//알파 렌더 (뿌려질DC, 알파값(투명도) 0 ~ 255)
	void alphaRender(HDC hdc, BYTE alpha);
	//알파 렌더 (뿌려질DC, 뿌릴좌표X, 뿌릴좌표Y , 알파값)
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	//알파 렌더 (뿌려질DC, 뿌릴좌표X(left),뿌릴좌표Y(top), 잘라올곳X(left), 잘라올곳Y(top), 잘라올 가로크기, 잘라올 세로크기, 알파값)
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//알파 프레임 렌더 (뿌려질DC, 뿌려질left,  뿌려질top, 알파값)
	void alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha);
	//알파 프레임 렌더(뿌려질DC, 뿌려질left, 뿌려질top, 프레임X번호, 프레임Y번호,알파값)
	void alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	//이미지 회전 렌더
	void rotateRender(HDC hdc, float centerX, float centerY, float angle);
	void alphaRotateRender(HDC hdc, float centerX, float centerY, float angle, BYTE alpha);
	void rotateFrameRender(HDC hdc, float centerX, float centerY, float angle);
	void rotateFrameRender(HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle);
	void alphaRotateFrameRender(HDC hdc, float centerX, float centerY, float angle, BYTE alpha);
	void alphaRotateFrameRender(HDC hdc, float centerX, float centerY, int currentFrameX, int currentFrameY, float angle, BYTE alpha);

	//루프 렌더
	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);


	//알파 세터, 게터 
	void setAlpha(int byte);
	BYTE getAlpha()
	{
		return _imageInfo->alpha;
	}

	//회전 세터, 게터
	void setRotationAngle(float angle);
	float getRotationAngle()
	{
		return _imageInfo->rotationAngle;
	}

	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//===================================
	// ## 이미지 관련 접근자, 설정자 ##
	//===================================

	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX() { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY() { return _imageInfo->y; }

	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ?
			_imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ?
			_imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);

	}

	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;

		//프레임번호가 최대프레임번호를 넘어가면 마지막 프레임으로 고정
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}

	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;

		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline int getFrameY() { return _imageInfo->currentFrameY; }

	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }

};

