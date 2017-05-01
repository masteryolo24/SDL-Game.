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
	imageRect.x =0;
	imageRect.y =0;
	imageRect.w = 1366;
	imageRect.h = 700;

	SoundGame = Mix_LoadWAV("sound/gameSound.wav");
	SoundSelect = Mix_LoadWAV("sound/selectMenu.wav");

	selectCharacter1 = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/select1.jpg");
	selectCharacter2 = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/select2.jpg");
	selectCharacter3 = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/select3.jpg");
	selectCharacter4 = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/select4.jpg");
	selectCharacter5 = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/select5.jpg");
	selectCharacter6 = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/select6.jpg");
	selectCharacter7 = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/select7.jpg");
	selectCharacter8 = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/select8.jpg");
	selectCharacter9 = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/select9.jpg");


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

	SDL_DestroyTexture(selectCharacter1);
	SDL_DestroyTexture(selectCharacter2);
	SDL_DestroyTexture(selectCharacter3);
	SDL_DestroyTexture(selectCharacter4);
	SDL_DestroyTexture(selectCharacter5);
	SDL_DestroyTexture(selectCharacter6);
	SDL_DestroyTexture(selectCharacter7);
	SDL_DestroyTexture(selectCharacter8);
	SDL_DestroyTexture(selectCharacter9);
}

void CMain::GameLoop(void) {
		SDL_GetMouseState(&MouseX, &MouseY);
		//std::cout << MouseX << "     " << MouseY << std::endl;

		ForestStage->DrawBackGround();

		character->Draw();
		character->Update();

		ForestStage->DrawObject();

		ForestStage->Update();
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
	case StateMenu:
		SDL_RenderClear(csdl_setup->GetRenderer());
		SDL_RenderCopy(csdl_setup->GetRenderer(), menu_image, NULL, &imageRect);
		break;
	case StateControl:
		SDL_RenderClear(csdl_setup->GetRenderer());
		SDL_RenderCopy(csdl_setup->GetRenderer(), control_imgae, NULL, &imageRect);
		break;
	case StateCredit:
		SDL_RenderClear(csdl_setup->GetRenderer());
		SDL_RenderCopy(csdl_setup->GetRenderer(), credit_image, NULL, &imageRect);
		break;
	case StateStory:
		SDL_RenderClear(csdl_setup->GetRenderer());
		SDL_RenderCopy(csdl_setup->GetRenderer(), story_image, NULL, &imageRect);
		break;
	case StateCharacter:
		SDL_RenderClear(csdl_setup->GetRenderer());
		SDL_RenderCopy(csdl_setup->GetRenderer(), selectCharacter_image, NULL, &imageRect);
		switch (csdl_setup->GetMainEvent()->key.keysym.sym) {
		case SDLK_1:
			delete character;
			SDL_RenderClear(csdl_setup->GetRenderer());
			SDL_RenderCopy(csdl_setup->GetRenderer(), selectCharacter1, NULL, &imageRect);
			character = new MainCharacter(csdl_setup, "image/character1.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			break;

		case SDLK_2:
			delete character;
			SDL_RenderClear(csdl_setup->GetRenderer());
			SDL_RenderCopy(csdl_setup->GetRenderer(), selectCharacter2, NULL, &imageRect);
			character = new MainCharacter(csdl_setup, "image/character2.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			break;

		case SDLK_3:
			delete character;
			SDL_RenderClear(csdl_setup->GetRenderer());
			SDL_RenderCopy(csdl_setup->GetRenderer(), selectCharacter3, NULL, &imageRect);
			character = new MainCharacter(csdl_setup, "image/character3.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			break;

		case SDLK_4:
			delete character;
			SDL_RenderClear(csdl_setup->GetRenderer());
			SDL_RenderCopy(csdl_setup->GetRenderer(), selectCharacter4, NULL, &imageRect);
			character = new MainCharacter(csdl_setup, "image/character4.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			break;

		case SDLK_5:
			delete character;
			SDL_RenderClear(csdl_setup->GetRenderer());
			SDL_RenderCopy(csdl_setup->GetRenderer(), selectCharacter5, NULL, &imageRect);
			character = new MainCharacter(csdl_setup, "image/character5.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			break;

		case SDLK_6:
			delete character;
			SDL_RenderClear(csdl_setup->GetRenderer());
			SDL_RenderCopy(csdl_setup->GetRenderer(), selectCharacter6, NULL, &imageRect);
			character = new MainCharacter(csdl_setup, "image/character6.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			break;

		case SDLK_7:
			delete character;
			SDL_RenderClear(csdl_setup->GetRenderer());
			SDL_RenderCopy(csdl_setup->GetRenderer(), selectCharacter7, NULL, &imageRect);
			character = new MainCharacter(csdl_setup, "image/character7.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			break;

		case SDLK_8:
			delete character;
			SDL_RenderClear(csdl_setup->GetRenderer());
			SDL_RenderCopy(csdl_setup->GetRenderer(), selectCharacter8, NULL, &imageRect);
			character = new MainCharacter(csdl_setup, "image/character8.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			break;

		case SDLK_9:
			delete character;
			SDL_RenderClear(csdl_setup->GetRenderer());
			SDL_RenderCopy(csdl_setup->GetRenderer(), selectCharacter9, NULL, &imageRect);
			character = new MainCharacter(csdl_setup, "image/character9.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			break;
		case SDLK_SPACE:
			gameState = StatePlaying;
			break;
		}

		break;
	case QuitGame:
		quit = true;
		break;
	case StatePlaying:
		GameLoop();
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


