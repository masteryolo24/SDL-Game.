#pragma once
#include "stdafx.h"
class CCollisionDetection
{
public:
	CCollisionDetection();
	CCollisionDetection(int x, int y, int w, int h);
	~CCollisionDetection(void);

	void SetRectangle(int x, int y, int w, int h);
	SDL_Rect GetRectangle() { return CollisionRect; }

	void SetX(int x) { CollisionRect.x = x + OffSetX; }
	void SetY(int y) { CollisionRect.y = y + OffSetY; }
private:
	int OffSetX;
	int OffSetY;

	SDL_Rect CollisionRect;

};
