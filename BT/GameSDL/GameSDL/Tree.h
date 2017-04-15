#pragma once
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Sprite.h"
class Tree
{
public:
	Tree(int x, int y, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup);
	~Tree(void);

	void DrawTrees();

	int GetX();
	int GetY();

	CSprite* GetTrees() { return Trees; }


private:
	int x;
	int y;
	CSprite* Trees;

};

