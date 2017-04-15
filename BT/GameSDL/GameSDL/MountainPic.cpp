#include "MountainPic.h"


MountainPic::MountainPic(int x_passed, int y_passed, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup)
{
	x = x_passed;
	y = y_passed;
	Mountain = new CSprite(csdl_setup->GetRenderer(), "image/map/mountain.png", x, y, 282, 270, CameraX, CameraY, CCollisionDetection(0, 135, 282, 100));
}


MountainPic::~MountainPic()
{
	delete Mountain;
}
int MountainPic::GetX() {
	return x;
}

int MountainPic::GetY() {
	return y;
}

void MountainPic::DrawMountain() {
	Mountain->Draw();
}
