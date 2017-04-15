#pragma once
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Sprite.h"
class CastlePic
{
public:
	CastlePic(int x, int y, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup);
	~CastlePic(void);

	void DrawCastle();

	int GetX();
	int GetY();

	CSprite* GetCastle() { return Castle; }

private:
	int x;
	int y;
	CSprite* Castle;
};

