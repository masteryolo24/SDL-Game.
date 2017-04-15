#pragma once
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Sprite.h"
class SoilPic
{
public:
	SoilPic(int x, int y, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup);
	~SoilPic(void);

	void DrawSoil();

	int GetX();
	int GetY();

	CSprite* GetSoil() { return Soil; }


private:
	int x;
	int y;
	CSprite* Soil;
};
