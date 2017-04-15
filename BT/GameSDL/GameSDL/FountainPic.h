#pragma once
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Sprite.h"
class FountainPic
{
public:
	FountainPic(int x, int y, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup);
	~FountainPic(void);

	void DrawFountain();

	int GetX();
	int GetY();

	CSprite* GetFountain() { return Fountain; }


private:
	int x;
	int y;
	CSprite* Fountain;
};

