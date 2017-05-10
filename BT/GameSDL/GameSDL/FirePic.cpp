#include "FirePic.h"


FirePic::FirePic(int x_passed, int y_passed, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup)
{
	x = x_passed;
	y = y_passed;
	Fire = new CSprite(csdl_setup->GetRenderer(), "image/fire.png", x, y, 46, 80, CameraX, CameraY, CCollisionDetection(0, 0, 46, 80));
}


FirePic::~FirePic()
{
	delete Fire;
}
int FirePic::GetX() {
	return x;
}

int FirePic::GetY() {
	return y;
}

void FirePic::DrawFire() {
	Fire->Draw();
	Fire->SetUpAnimation(8, 1);
	Fire->PlayAnimation(0, 7, 0, 100);
}
