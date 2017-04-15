#pragma once
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Sprite.h"
class TentPic
{
public:
	TentPic(int x, int y, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup);
	~TentPic(void);

	void DrawTent();

	int GetX();
	int GetY();

	CSprite* GetTent() { return Tent; }


private:
	int x;
	int y;
	CSprite* Tent;
};
