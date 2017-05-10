#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "SDL_Setup.h"
#include "MapGame.h"
#include <math.h>
class MainCharacter
{
public:
	MainCharacter(CSDL_Setup* passed_SDL_Setup, std::string FilePath, int *passed_MouseX, int *passed_MouseY, float *CameraX, float *CameraY, CMapGame* passed_Enviroment);
	~MainCharacter();

	float GetDistance(int X1, int Y1, int X2, int Y2);

	void Update();
	void Draw();
	void DrawMouse();
	int gameOver;
private:
	CMapGame *Enviroment;

	void UpdateAnimation();
	void UpdateControls();

	float *CameraX;
	float *CameraY;

	int *MouseX;
	int *MouseY;

	CSDL_Setup *csdl_setup;

	CSprite* character;
	int timeCheck;

	bool Follow;
	int Follow_Point_X;
	int Follow_Point_Y;

	int Follow_Point_X1;
	int Follow_Point_Y1;

	float distance;
	bool stopAnimation;

	bool Colliding;
	bool Dead;

	SDL_Texture* click;
	SDL_Texture* clickEffect;
	SDL_Rect clickRect;
	SDL_Rect effectRect;

	

};



