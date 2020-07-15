#include "stdafx.h"
#include "saveLoadTest.h"


saveLoadTest::saveLoadTest()
{
}


saveLoadTest::~saveLoadTest()
{
}

void saveLoadTest::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) save();
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) load();
}

void saveLoadTest::save()
{
	//파일 입출력은 굉장히 다양한 방식이 존재한다
	//C 플랫폼에선 FILE* 를 사용 (기능 없고, 빠름)
	//C++ 플랫폼에선 ifstream, ofstream을 사용
	//(기능 많고, 대신 느림)
	//Win32 플랫폼에선 CreateFile() 이란 함수가 있다.

	//나중에 공부해서 자기가 하기 편한걸로 ㅊㅊ
	//멀리 내다보면 ifstream, ofstream을 공부해보는걸 추천한다

	HANDLE file;
	DWORD write;

	char str[128] = "반장 인상쓰는거 준나 카리스마 있어";

	file = CreateFile("17기의카리스마담당.txt", GENERIC_WRITE,
		FALSE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);

	CloseHandle(file);


}

void saveLoadTest::load()
{
	HANDLE file;
	DWORD read;

	char str[128];

	file = CreateFile("17기의카리스마담당.txt", GENERIC_READ,
		FALSE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, strlen(str), &read, NULL);

	CloseHandle(file);

	MessageBox(_hWnd, str, "1주일준포폴화이팅", MB_OK);
}
