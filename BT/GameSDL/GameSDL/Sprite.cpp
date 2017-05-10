#include "Sprite.h"

CSprite::CSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, float *passed_CameraX, float *passed_CameraY, CCollisionDetection passed_CollisionRect)
{
	CollisionRect = passed_CollisionRect;

	renderer = passed_renderer;
	image = NULL;
	image = IMG_LoadTexture(renderer, FilePath.c_str());
	if (image == NULL) {
		std::cout << "Can not load " << FilePath.c_str() << std::endl;
	}
	CollisionImage = NULL;
	CollisionImage = IMG_LoadTexture(renderer, "image/CollisionBox/box.png");

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_QueryTexture(image, NULL, NULL, &img_width, &img_height);

	crop.x = 0;
	crop.y = 0;
	crop.w = img_width;
	crop.h = img_height;

	CurrentFrame = 0;
	animationDelay = SDL_GetTicks();

	Amount_Frame_X = 0;
	Amount_Frame_Y = 0;

	CameraX = passed_CameraX;
	CameraY = passed_CameraY;

	Camera.x = rect.x + *CameraX;
	Camera.y = rect.y + *CameraY;
	Camera.w = rect.w;
	Camera.h = rect.h;
}

CSprite::~CSprite()
{
	SDL_DestroyTexture(image);
}

void CSprite::SetUpAnimation(int passed_Amount_X, int passed_Amount_Y) {
	Amount_Frame_X = passed_Amount_X;
	Amount_Frame_Y = passed_Amount_Y;
}

void CSprite::PlayAnimation(int BeginFrame, int EndFrame, int Row, float Speed) {
	if (animationDelay + Speed < SDL_GetTicks())
	{
		if (EndFrame <= CurrentFrame) {
			CurrentFrame = BeginFrame;
		}
		else CurrentFrame++;
		crop.x = CurrentFrame * (img_width / Amount_Frame_X);
		crop.y = Row * (img_height / Amount_Frame_Y);
		crop.w = img_width / Amount_Frame_X;
		crop.h = img_height / Amount_Frame_Y;

		animationDelay = SDL_GetTicks();
	}
	
}


void CSprite::Draw() {
	Camera.x = rect.x + *CameraX;
	Camera.y = rect.y + *CameraY;

	CollisionRect.SetX(Camera.x);
	CollisionRect.SetY(Camera.y);

	SDL_RenderCopy(renderer, image, &crop, &Camera);

	SDL_RenderCopy(renderer, CollisionImage, NULL, &CollisionRect.GetRectangle());
}

void CSprite::DrawSteady() {

	SDL_RenderCopy(renderer, image, &crop, &rect);
	SDL_RenderCopy(renderer, CollisionImage, NULL, &CollisionRect.GetRectangle());
}



bool CSprite::isColliding(CCollisionDetection theCollider) {
	return !(CollisionRect.GetRectangle().x + CollisionRect.GetRectangle().w < theCollider.GetRectangle().x ||
		CollisionRect.GetRectangle().y + CollisionRect.GetRectangle().h < theCollider.GetRectangle().y ||
		CollisionRect.GetRectangle().x > theCollider.GetRectangle().x + theCollider.GetRectangle().w ||
		CollisionRect.GetRectangle().y > theCollider.GetRectangle().y + theCollider.GetRectangle().h);
}