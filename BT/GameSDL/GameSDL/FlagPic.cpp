#include "stdafx.h"
#include "FlagPic.h"

FlagPic::FlagPic(int x_passed, int y_passed, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup)
{
	x = x_passed;
	y = y_passed;
	Flag = new CSprite(csdl_setup->GetRenderer(), "image/map/flag.png", x, y, 34, 89, CameraX, CameraY, CCollisionDetection());
}

FlagPic::~FlagPic(void)
{
	delete Flag;
}

int FlagPic::GetX() {
	return x;
}

int FlagPic::GetY() {
	return y;
}

void FlagPic::DrawFlag() {
	Flag->Draw();
}