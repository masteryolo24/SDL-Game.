#include "stdafx.h"
#include "Main.h"

CMain::CMain(int passed_ScreenWidth, int passed_ScreenHeight)
{
	CameraX = 0;
	CameraY = 0;

	ScreenHeight = passed_ScreenHeight;
	ScreenWidth = passed_ScreenWidth;

	quit = false;

	csdl_setup = new CSDL_Setup(quit, ScreenWidth, ScreenHeight);

	ForestStage = new CMapGame(ScreenWidth, ScreenHeight, &CameraX, &CameraY, csdl_setup);

	MouseX = 0;
	MouseY = 0;

	OnePressed = false;
	OnePressed1 = false;
	character = new MainCharacter(csdl_setup, "image/character1.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);

	gameState = StateMenu;

	menu_image = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/menu.jpg");
	credit_image = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/credit.jpg");
	control_imgae = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/control.jpg");
	story_image = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/story.jpg");
	selectCharacter_image = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/selectCharacter.jpg");
	controlingame_image = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/controlingame.jpg");
	gameover = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/dead.jpg");
	imageRect.x =0;
	imageRect.y =0;
	imageRect.w = 1366;
	imageRect.h = 700;

	SoundGame = Mix_LoadWAV("sound/gameSound.wav");
	SoundSelect = Mix_LoadWAV("sound/selectMenu.wav");

}

CMain::~CMain(void)
{
	delete csdl_setup;

	delete character;

	delete ForestStage;

	Mix_FreeChunk(SoundGame);
	Mix_FreeChunk(SoundSelect);

	SDL_DestroyTexture(menu_image);
	SDL_DestroyTexture(credit_image);
	SDL_DestroyTexture(control_imgae);
	SDL_DestroyTexture(story_image);
	SDL_DestroyTexture(selectCharacter_image);
	SDL_DestroyTexture(gameover);

}

void CMain::GameLoop(void) {
		SDL_GetMouseState(&MouseX, &MouseY);

		ForestStage->DrawBackGround();

		character->Draw();
		character->Update();

		ForestStage->DrawObject();

		ForestStage->Update();
		character->DrawMouse();
}

void CMain::OnGame() {
		if (gameState == StateMenu) {
			if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN) {
				if (!OnePressed) {
					switch (csdl_setup->GetMainEvent()->key.keysym.sym) {
					case SDLK_RETURN:
						gameState = StateCharacter;
						Mix_PlayChannel(4, SoundGame, -1);
						OnePressed = true;
						break;

					case SDLK_1:
						Mix_PlayChannel(5, SoundSelect, 0);
						gameState = StateControl;
						OnePressed = true;
						break;

					case SDLK_2:
						Mix_PlayChannel(5, SoundSelect, 0);
						gameState = StateCredit;
						OnePressed = true;
						break;

					case SDLK_3:
						Mix_PlayChannel(5, SoundSelect, 0);
						gameState = StateStory;
						OnePressed = true;
						break;

					case SDLK_ESCAPE:
						gameState = QuitGame;
						OnePressed = true;
						break;
					}
				}
			}

			if (csdl_setup->GetMainEvent()->type == SDL_KEYUP) {
				if (OnePressed) {
					switch (csdl_setup->GetMainEvent()->key.keysym.sym) {
					case SDLK_RETURN:
						OnePressed = false;
						break;
					case SDLK_1:
						OnePressed = false;
						break;
					case SDLK_2:
						OnePressed = false;
						break;
					case SDLK_3:
						OnePressed = false;
						break;
					case SDLK_ESCAPE:
						OnePressed = false;
						break;
					}
				}
			}
		}
		else if (gameState == StateCredit || gameState == StateControl || gameState == StateStory || gameState == StateCharacter) {
			if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
				if (csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_ESCAPE) {
					Mix_PlayChannel(5, SoundSelect, 0);
					gameState = StateMenu;
				}
		}

		if (csdl_setup->GetMainEvent()->type == SDL_QUIT)
			quit = true;
}

void CMain::OnRender() {
	switch (gameState) {
	case GameOver:
		SDL_RenderCopy(csdl_setup->GetRenderer(), gameover, NULL, &imageRect);
		if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN) {
			if (csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_y) {
				gameState = StateMenu;
			}
			else if (csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_n) {
				gameState = QuitGame;
			}
		}
		break;
	case StateMenu:
		SDL_RenderCopy(csdl_setup->GetRenderer(), menu_image, NULL, &imageRect);
		break;
	case StateControl:
		SDL_RenderCopy(csdl_setup->GetRenderer(), control_imgae, NULL, &imageRect);
		break;
	case StateCredit:
		SDL_RenderCopy(csdl_setup->GetRenderer(), credit_image, NULL, &imageRect);
		break;
	case StateStory:
		SDL_RenderCopy(csdl_setup->GetRenderer(), story_image, NULL, &imageRect);
		break;
	case StateCharacter:
		SDL_RenderCopy(csdl_setup->GetRenderer(), selectCharacter_image, NULL, &imageRect);
		switch (csdl_setup->GetMainEvent()->key.keysym.sym) {
		case SDLK_1:
			delete character;
			character = new MainCharacter(csdl_setup, "image/character1.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			gameState = StatePlaying;
			break;

		case SDLK_2:
			delete character;
			character = new MainCharacter(csdl_setup, "image/character2.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			gameState = StatePlaying;
			break;

		case SDLK_3:
			delete character;
			character = new MainCharacter(csdl_setup, "image/character3.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			gameState = StatePlaying;
			break;

		case SDLK_4:
			delete character;
			character = new MainCharacter(csdl_setup, "image/character4.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			gameState = StatePlaying;
			break;

		case SDLK_5:
			delete character;
			character = new MainCharacter(csdl_setup, "image/character5.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			gameState = StatePlaying;
			break;

		case SDLK_6:
			delete character;
			character = new MainCharacter(csdl_setup, "image/character6.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			gameState = StatePlaying;
			break;

		case SDLK_7:
			delete character;
			character = new MainCharacter(csdl_setup, "image/character7.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			gameState = StatePlaying;
			break;

		case SDLK_8:
			delete character;
			character = new MainCharacter(csdl_setup, "image/character8.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			gameState = StatePlaying;
			break;

		case SDLK_9:
			delete character;
			character = new MainCharacter(csdl_setup, "image/character9.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			gameState = StatePlaying;
			break;
		}

		break;
	case QuitGame:
		quit = true;
		break;
	case StatePlaying:
		GameLoop();
		if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN) {
			if (csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F1) {
				SDL_RenderClear(csdl_setup->GetRenderer());
				SDL_RenderCopy(csdl_setup->GetRenderer(), controlingame_image, NULL, &imageRect);
			}
		}
		if (csdl_setup->GetMainEvent()->type == SDL_KEYUP) {
			if (csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F1) {
				GameLoop();
			}
		}
		
		if (character->gameOver == 1) {
			gameState = GameOver;
			Mix_HaltChannel(4);
			
		}
		break;
	}
}


void CMain::OnExecute() {
	while (!quit && csdl_setup->GetMainEvent()->type != SDL_QUIT) {
		csdl_setup->Begin();
		OnGame();
		OnRender();
		csdl_setup->End();
	}
}


