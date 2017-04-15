#include "stdafx.h"
#include "FountainPic.h"

FountainPic::FountainPic(int x_passed, int y_passed, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup)
{
	x = x_passed;
	y = y_passed;
	Fountain = new CSprite(csdl_setup->GetRenderer(), "image/map/fountain.png", x, y, 114, 96, CameraX, CameraY, CCollisionDetection(0, 50, 114, 40));
}

FountainPic::~FountainPic(void)
{
	delete Fountain;
}

int  FountainPic::GetX() {
	return x;
}

int FountainPic::GetY() {
	return y;
}

void FountainPic::DrawFountain() {
	Fountain->Draw();
}