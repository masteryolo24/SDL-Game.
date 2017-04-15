#include "stdafx.h"
#include "TentPic.h"

TentPic::TentPic(int x_passed, int y_passed, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup)
{
	x = x_passed;
	y = y_passed;
	Tent = new CSprite(csdl_setup->GetRenderer(), "image/map/tent.png", x, y, 144, 142, CameraX, CameraY, CCollisionDetection( 0 , 70 , 144 , 65));
}

TentPic::~TentPic(void)
{
	delete Tent;
}

int  TentPic::GetX() {
	return x;
}

int TentPic::GetY() {
	return y;
}

void TentPic::DrawTent() {
	Tent->Draw();
}