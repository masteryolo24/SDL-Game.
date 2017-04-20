#include "MainCharacter.h"

MainCharacter::MainCharacter(CSDL_Setup* passed_SDL_Setup, std::string FilePath, int *passed_MouseX, int *passed_MouseY, float *passed_CameraX, float *passed_CameraY, CMapGame* passed_Enviroment)
{
	Enviroment = passed_Enviroment;

	CameraX = passed_CameraX;
	CameraY = passed_CameraY;

	csdl_setup = passed_SDL_Setup;
	MouseX = passed_MouseX;
	MouseY = passed_MouseY;

	character = new CSprite(csdl_setup->GetRenderer(), FilePath, 300, 250, 42, 42, CameraX, CameraY, CCollisionDetection(306, 256, 37, 42));

	character->SetUpAnimation(3, 4);
	timeCheck = SDL_GetTicks();
	Follow = false;
	distance = 0;
	stopAnimation = false;
}

MainCharacter::~MainCharacter()
{
	delete character;
}

double MainCharacter::GetDistance(int X1, int Y1, int X2, int Y2) {
	double DifferenceX = X1 - X2;
	double DifferenceY = Y1 - Y2;
	double distance = sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
	return distance;
}

void MainCharacter::Draw() {
	character->DrawSteady();
}

void MainCharacter::UpdateAnimation() {
	float angle = atan2(Follow_Point_Y - *CameraY, Follow_Point_X - *CameraX);
	angle = angle *(180 / 3.14) + 180;
	if (!stopAnimation) {
		if (angle > 45 && angle <= 135) {
			if (distance > 15)
				character->PlayAnimation(0, 1, 0, 100);
			else character->PlayAnimation(1, 1, 0, 100);
		}
		else if (angle > 135 && angle <= 225)
		{
			if (distance > 15)
				character->PlayAnimation(0, 1, 1, 100);
			else character->PlayAnimation(1, 1, 1, 100);
		}
		else if (angle > 225 && angle <= 315) {
			if (distance > 15)
				character->PlayAnimation(0, 1, 3, 100);
			else character->PlayAnimation(1, 1, 3, 100);
		}
		else if ((angle <= 360 && angle < 315) || (angle > 0 && angle <= 45)) {
			if (distance > 15)
				character->PlayAnimation(0, 1, 2, 100);
			else character->PlayAnimation(1, 1, 2, 100);
		}
	}
}

void MainCharacter::UpdateControls() {
	if (csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN || csdl_setup->GetMainEvent()->type == SDL_MOUSEMOTION) {
		if (csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
		{
			Follow_Point_X = *CameraX - *MouseX + 300;
			Follow_Point_Y = *CameraY - *MouseY + 250;
			Follow = true;
		}
	}

	if (timeCheck + 5 < SDL_GetTicks() && Follow)
	{
		distance = GetDistance(*CameraX, *CameraY, Follow_Point_X, Follow_Point_Y);
		if (distance == 0)
			stopAnimation = true;
		else
			stopAnimation = false;

		bool Colliding = false;

		if (distance > 15)
		{
			for (int i = 0; i < Enviroment->GetTrees().size(); i++) {
				if (character->isColliding(Enviroment->GetTrees()[i]->GetTrees()->GetCollisionRect())) {
					if (*CameraX > Follow_Point_X) {
						*CameraX = *CameraX + 5;
					}
					if (*CameraX < Follow_Point_X) {
						*CameraX = *CameraX - 5;
					}

					if (*CameraY > Follow_Point_Y) {
						*CameraY = *CameraY + 5;
					}
					if (*CameraY < Follow_Point_Y) {
						*CameraY = *CameraY - 5;
					}

					Follow_Point_X = *CameraX;
					Follow_Point_Y = *CameraY;
					distance = 0;
					Follow = false;

					Colliding = true;
				}
			}

			for (int i = 0; i < Enviroment->GetWater().size(); i++) {
				if (character->isColliding(Enviroment->GetWater()[i]->GetWater()->GetCollisionRect())) {
					if (*CameraX > Follow_Point_X) {
						*CameraX = *CameraX + 5;
					}
					if (*CameraX < Follow_Point_X) {
						*CameraX = *CameraX - 5;
					}

					if (*CameraY > Follow_Point_Y) {
						*CameraY = *CameraY + 5;
					}
					if (*CameraY < Follow_Point_Y) {
						*CameraY = *CameraY - 5;
					}

					Follow_Point_X = *CameraX;
					Follow_Point_Y = *CameraY;
					distance = 0;
					Follow = false;

					Colliding = true;
				}
			}

			for (int i = 0; i < Enviroment->GetMountain().size(); i++) {
				if (character->isColliding(Enviroment->GetMountain()[i]->GetMountain()->GetCollisionRect())) {
					if (*CameraX > Follow_Point_X) {
						*CameraX = *CameraX + 5;
					}
					if (*CameraX < Follow_Point_X) {
						*CameraX = *CameraX - 5;
					}

					if (*CameraY > Follow_Point_Y) {
						*CameraY = *CameraY + 5;
					}
					if (*CameraY < Follow_Point_Y) {
						*CameraY = *CameraY - 5;
					}

					Follow_Point_X = *CameraX;
					Follow_Point_Y = *CameraY;
					distance = 0;
					Follow = false;

					Colliding = true;
				}
			}

			for (int i = 0; i < Enviroment->GetCastle().size(); i++) {
				if (character->isColliding(Enviroment->GetCastle()[i]->GetCastle()->GetCollisionRect())) {
					if (*CameraX > Follow_Point_X) {
						*CameraX = *CameraX + 5;
					}
					if (*CameraX < Follow_Point_X) {
						*CameraX = *CameraX - 5;
					}

					if (*CameraY > Follow_Point_Y) {
						*CameraY = *CameraY + 5;
					}
					if (*CameraY < Follow_Point_Y) {
						*CameraY = *CameraY - 5;
					}

					Follow_Point_X = *CameraX;
					Follow_Point_Y = *CameraY;
					distance = 0;
					Follow = false;

					Colliding = true;
				}
			}

			for (int i = 0; i < Enviroment->GetFountain().size(); i++) {
				if (character->isColliding(Enviroment->GetFountain()[i]->GetFountain()->GetCollisionRect())) {
					if (*CameraX > Follow_Point_X) {
						*CameraX = *CameraX + 5;
					}
					if (*CameraX < Follow_Point_X) {
						*CameraX = *CameraX - 5;
					}

					if (*CameraY > Follow_Point_Y) {
						*CameraY = *CameraY + 5;
					}
					if (*CameraY < Follow_Point_Y) {
						*CameraY = *CameraY - 5;
					}

					Follow_Point_X = *CameraX;
					Follow_Point_Y = *CameraY;
					distance = 0;
					Follow = false;

					Colliding = true;
				}
			}

			for (int i = 0; i < Enviroment->GetTent().size(); i++) {
				if (character->isColliding(Enviroment->GetTent()[i]->GetTent()->GetCollisionRect())) {
					if (*CameraX > Follow_Point_X) {
						*CameraX = *CameraX + 5;
					}
					if (*CameraX < Follow_Point_X) {
						*CameraX = *CameraX - 5;
					}

					if (*CameraY > Follow_Point_Y) {
						*CameraY = *CameraY + 5;
					}
					if (*CameraY < Follow_Point_Y) {
						*CameraY = *CameraY - 5;
					}

					Follow_Point_X = *CameraX;
					Follow_Point_Y = *CameraY;
					distance = 0;
					Follow = false;

					Colliding = true;
				}
			}

			if (!Colliding) {
				if (*CameraY != Follow_Point_Y) {
					*CameraY = *CameraY - (((*CameraY - Follow_Point_Y) / distance) *1.5f);
				}

				if (*CameraX != Follow_Point_X) {
					*CameraX = *CameraX - (((*CameraX - Follow_Point_X) / distance) *1.5f);
				}
			}
		}
		else
			Follow = false;
		timeCheck = SDL_GetTicks();
	}
}

void MainCharacter::Update() {
	UpdateAnimation();
	UpdateControls();
}