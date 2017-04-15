#include "stdafx.h"
#include "WheatPic.h"

WheatPic::WheatPic(int x_passed, int y_passed, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup)
{
	x = x_passed;
	y = y_passed;
	Wheat = new CSprite(csdl_setup->GetRenderer(), "image/map/wheat.png", x, y, 48, 47, CameraX, CameraY, CCollisionDetection());
}

WheatPic::~WheatPic(void)
{
	delete Wheat;
}

int  WheatPic::GetX() {
	return x;
}

int WheatPic::GetY() {
	return y;
}

void WheatPic::DrawWheat() {
	Wheat->Draw();
}