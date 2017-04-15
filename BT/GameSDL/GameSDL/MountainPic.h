#pragma once
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Sprite.h"
class MountainPic
{
public:
	MountainPic(int x, int y, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup);
	~MountainPic(void);

	void DrawMountain();

	int GetX();
	int GetY();

	CSprite* GetMountain() { return Mountain; }

private:
	int x;
	int y;
	CSprite* Mountain;
};

