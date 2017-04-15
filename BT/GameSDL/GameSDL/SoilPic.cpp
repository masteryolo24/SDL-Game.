#include "stdafx.h"
#include "SoilPic.h"

SoilPic::SoilPic(int x_passed, int y_passed, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup)
{
	x = x_passed;
	y = y_passed;
	Soil = new CSprite(csdl_setup->GetRenderer(), "image/map/soil.png", x, y, 96, 96, CameraX, CameraY , CCollisionDetection());
}

SoilPic::~SoilPic(void)
{
	delete Soil;
}

int  SoilPic::GetX() {
	return x;
}

int SoilPic::GetY() {
	return y;
}

void SoilPic::DrawSoil() {
	Soil->Draw();
}