#pragma once
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Sprite.h"
class FlagPic
{
public:
	FlagPic(int x, int y, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup);
	~FlagPic(void);

	void DrawFlag();

	int GetX();
	int GetY();

	CSprite* GetFlag() { return Flag; }


private:
	int x;
	int y;
	CSprite* Flag;
};

