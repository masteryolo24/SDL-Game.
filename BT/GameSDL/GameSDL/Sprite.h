#pragma once
#include "stdafx.h"
#include "CollisionDetection.h"

class CSprite
{
public:
	CSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, float *CameraX, float *CameraY, CCollisionDetection passed_CollisionRect);
	~CSprite();

	void Draw();
	void DrawSteady();

	void SetPosition(float X, float Y);

	float GetX() { return X_pos; }
	float GetY() { return Y_pos; }

	void PlayAnimation(int BeginFrame, int EndFrame, int Row, float Speed);
	void SetUpAnimation(int passed_Amount_X, int passed_Amount_Y);

	bool isColliding(CCollisionDetection theCollider);

	CCollisionDetection GetCollisionRect() { return CollisionRect; }

private:
	SDL_Rect Camera;

	CCollisionDetection CollisionRect;

	float *CameraX;
	float *CameraY;

	float X_pos;
	float Y_pos;

	SDL_Texture* image;
	SDL_Texture* CollisionImage;

	SDL_Rect rect;
	SDL_Rect crop;

	int img_width;
	int img_height;
	int CurrentFrame;
	int animationDelay;

	int Amount_Frame_X;
	int Amount_Frame_Y;

	SDL_Renderer* renderer;
};
