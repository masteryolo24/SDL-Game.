#pragma once
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Sprite.h"
class WheatPic
{
public:
	WheatPic(int x, int y, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup);
	~WheatPic(void);

	void DrawWheat();

	int GetX();
	int GetY();

	CSprite* GetWheat() { return Wheat; }


private:
	int x;
	int y;
	CSprite* Wheat;
};
