#pragma once
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Sprite.h"
class MagicBook
{
public:
	MagicBook(int x, int y, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup);
	~MagicBook(void);

	void DrawBook();

	int GetX();
	int GetY();

	CSprite* GetBook() { return Book; }

private:
	int x;
	int y;
	CSprite* Book;
};

