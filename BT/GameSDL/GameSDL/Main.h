#pragma once
#include "SDL_Setup.h"
#include  "Sprite.h"
#include <math.h>
#include "MainCharacter.h"
#include "MapGame.h"
#include "SDL.h"


class CMain
{
public:
	CMain(int passedScreenWidth, int passedScreenHeight);
	~CMain();
	void OnExecute();
	void GameLoop();
	void OnGame();
	void OnRender();
private:

	enum GameState
	{
		StateMenu,
		StateControl,
		StateCredit,
		StatePlaying,
		StateStory,
		StateCharacter,
		QuitGame
	};

	float CameraX;
	float CameraY;

	MainCharacter *character;
	CMapGame* ForestStage;

	int ScreenWidth;
	int ScreenHeight;
	bool quit;

	bool OnePressed;
	bool OnePressed1;

	CSDL_Setup* csdl_setup;

	int MouseX;
	int MouseY;

	SDL_Event event;
	int gameState;

	Mix_Chunk* SoundGame;
	Mix_Chunk* SoundSelect;

	SDL_Texture* menu_image = NULL;
	SDL_Texture* credit_image = NULL;
	SDL_Texture* control_imgae = NULL;
	SDL_Texture* story_image = NULL;
	SDL_Texture* selectCharacter_image = NULL;
	SDL_Rect imageRect;

	SDL_Texture* selectCharacter1 = NULL;
	SDL_Texture* selectCharacter2 = NULL;
	SDL_Texture* selectCharacter3 = NULL;
	SDL_Texture* selectCharacter4 = NULL;
	SDL_Texture* selectCharacter5 = NULL;
	SDL_Texture* selectCharacter6 = NULL;
	SDL_Texture* selectCharacter7 = NULL;
	SDL_Texture* selectCharacter8 = NULL;
	SDL_Texture* selectCharacter9 = NULL;
};
