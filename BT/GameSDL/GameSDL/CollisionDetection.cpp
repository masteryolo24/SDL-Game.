#include "CollisionDetection.h"



CCollisionDetection::CCollisionDetection()
{
	OffSetX = 0;
	OffSetY = 0;
	SetRectangle(0, 0, 0, 0);
}

CCollisionDetection::CCollisionDetection(int x, int y, int w, int h)
{
	OffSetX = x;
	OffSetY = y;
	SetRectangle(0, 0, w, h);
}


CCollisionDetection::~CCollisionDetection()
{
}

void CCollisionDetection::SetRectangle(int x, int y, int w, int h) {
	CollisionRect.x = x + OffSetX;
	CollisionRect.y = y + OffSetY;
	CollisionRect.w = w;
	CollisionRect.h = h;
}