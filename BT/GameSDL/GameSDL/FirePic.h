#pragma once
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Sprite.h"
class FirePic
{
public:
	FirePic(int x, int y, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup);
	~FirePic(void);

	void DrawFire();

	int GetX();
	int GetY();

	CSprite* GetFire() { return Fire; }

private:
	int x;
	int y;
	CSprite* Fire;
};

