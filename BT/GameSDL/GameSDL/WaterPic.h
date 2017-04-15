#pragma once
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Sprite.h"
class WaterPic
{
public:
	WaterPic(int x, int y, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup);
	~WaterPic(void);

	void DrawWater();

	int GetX();
	int GetY();

	CSprite* GetWater() { return Water; }


private:
	int x;
	int y;
	CSprite* Water;
};
