#include "Tree.h"

Tree::Tree(int x_passed, int y_passed, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup)
{
	x = x_passed;
	y = y_passed;
	Trees = new CSprite(csdl_setup->GetRenderer(), "image/map/tree1.png", x, y, 120, 145, CameraX, CameraY, CCollisionDetection(40, 100, 35, 30));
}

Tree::~Tree(void)
{
	delete Trees;
}

int  Tree::GetX() {
	return x;
}

int Tree::GetY() {
	return y;
}

void Tree::DrawTrees() {
	Trees->Draw();
}