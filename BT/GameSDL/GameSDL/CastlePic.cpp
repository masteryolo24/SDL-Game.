#include "CastlePic.h"


CastlePic::CastlePic(int x_passed, int y_passed, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup)
{
	x = x_passed;
	y = y_passed;
	Castle = new CSprite(csdl_setup->GetRenderer(), "image/map/castle.png", x, y, 200, 200, CameraX, CameraY, CCollisionDetection(0, 120, 200, 70));
}


CastlePic::~CastlePic()
{
	delete Castle;
}
int CastlePic::GetX() {
	return x;
}

int CastlePic::GetY() {
	return y;
}

void CastlePic::DrawCastle() {
	Castle->Draw();
}
