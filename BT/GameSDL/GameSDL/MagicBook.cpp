#include "stdafx.h"
#include "MagicBook.h"

MagicBook::MagicBook(int x_passed, int y_passed, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup)
{
	x = x_passed;
	y = y_passed;
	Book = new CSprite(csdl_setup->GetRenderer(), "image/magicbook.png", x, y, 35, 35, CameraX, CameraY, CCollisionDetection(0, 0, 35, 35));
}

MagicBook::~MagicBook(void)
{
	delete Book;
}

int  MagicBook::GetX() {
	return x;
}

int MagicBook::GetY() {
	return y;
}

void MagicBook::DrawBook() {
	Book->Draw();
}