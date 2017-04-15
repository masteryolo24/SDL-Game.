#include "stdafx.h"
#include "WaterPic.h"

WaterPic::WaterPic(int x_passed, int y_passed, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup)
{
	x = x_passed;
	y = y_passed;
	Water = new CSprite(csdl_setup->GetRenderer(), "image/map/water.png", x, y, 100, 75, CameraX, CameraY, CCollisionDetection(0, 0, 100, 75));
}

WaterPic::~WaterPic(void)
{
	delete Water;
}

int  WaterPic::GetX() {
	return x;
}

int WaterPic::GetY() {
	return y;
}

void WaterPic::DrawWater() {
	Water->Draw();
}