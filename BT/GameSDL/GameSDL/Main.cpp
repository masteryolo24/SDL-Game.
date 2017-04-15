#include "stdafx.h"
#include "Main.h"

CMain::CMain(int passed_ScreenWidth, int passed_ScreenHeight)
{
	CameraX = 0;
	CameraY = 0;

	ScreenHeight = passed_ScreenHeight;
	ScreenWidth = passed_ScreenWidth;

	quit = false;

	csdl_setup = new CSDL_Setup(&quit, ScreenWidth, ScreenHeight);

	ForestStage = new CMapGame(ScreenWidth, ScreenHeight, &CameraX, &CameraY, csdl_setup);

	MouseX = 0;
	MouseY = 0;

	OnePressed = false;
	OnePressed1 = false;
	character = new MainCharacter(csdl_setup, "image/character1.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);

	gameState = StateMenu;

	menu_image = IMG_LoadTexture(csdl_setup->renderer, "image/menu.jpg");
	credit_image = IMG_LoadTexture(csdl_setup->renderer, "image/credit.jpg");
	control_imgae = IMG_LoadTexture(csdl_setup->renderer, "image/control.jpg");
	story_image = IMG_LoadTexture(csdl_setup->renderer, "image/story.jpg");
	selectCharacter_image = IMG_LoadTexture(csdl_setup->renderer, "image/selectCharacter.jpg");
	imageRect.x = 0;
	imageRect.y = 0;
	imageRect.w = 1366;
	imageRect.h = 700;

	SoundGame = Mix_LoadWAV("sound/gameSound.wav");
	SoundSelect = Mix_LoadWAV("sound/selectMenu.wav");

	selectCharacter1 = IMG_LoadTexture(csdl_setup->renderer, "image/select1.jpg");
	selectCharacter2 = IMG_LoadTexture(csdl_setup->renderer, "image/select2.jpg");
	selectCharacter3 = IMG_LoadTexture(csdl_setup->renderer, "image/select3.jpg");
	selectCharacter4 = IMG_LoadTexture(csdl_setup->renderer, "image/select4.jpg");
	selectCharacter5 = IMG_LoadTexture(csdl_setup->renderer, "image/select5.jpg");
	selectCharacter6 = IMG_LoadTexture(csdl_setup->renderer, "image/select6.jpg");
	selectCharacter7 = IMG_LoadTexture(csdl_setup->renderer, "image/select7.jpg");
	selectCharacter8 = IMG_LoadTexture(csdl_setup->renderer, "image/select8.jpg");
	selectCharacter9 = IMG_LoadTexture(csdl_setup->renderer, "image/select9.jpg");


}

CMain::~CMain(void)
{
	delete csdl_setup;

	delete character;

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
	while (!quit && csdl_setup->GetMainEvent()->type != SDL_QUIT) {
		csdl_setup->Begin();
		SDL_GetMouseState(&MouseX, &MouseY);

		ForestStage->DrawBackGround();

		character->Draw();
		character->Update();

		ForestStage->DrawObject();

		ForestStage->Update();
		csdl_setup->End();

	}
}

void CMain::OnGame() {
	while (SDL_PollEvent(&event)) {
		if (gameState == StateMenu) {
			if (event.type == SDL_KEYDOWN) {
				if (!OnePressed) {
					switch (event.key.keysym.sym) {
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

			if (event.type == SDL_KEYUP) {
				if (OnePressed) {
					switch (event.key.keysym.sym) {
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
			if (event.type == SDL_KEYDOWN)
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					Mix_PlayChannel(5, SoundSelect, 0);
					gameState = StateMenu;
				}
		}

		if (event.type == SDL_QUIT)
			quit = true;
	}
}

void CMain::OnRender() {
	switch (gameState) {
	case StateMenu:
		SDL_RenderClear(csdl_setup->renderer);
		SDL_RenderCopy(csdl_setup->renderer, menu_image, NULL, &imageRect);
		break;
	case StateControl:
		SDL_RenderClear(csdl_setup->renderer);
		SDL_RenderCopy(csdl_setup->renderer, control_imgae, NULL, &imageRect);
		break;
	case StateCredit:
		SDL_RenderClear(csdl_setup->renderer);
		SDL_RenderCopy(csdl_setup->renderer, credit_image, NULL, &imageRect);
		break;
	case StateStory:
		SDL_RenderClear(csdl_setup->renderer);
		SDL_RenderCopy(csdl_setup->renderer, story_image, NULL, &imageRect);
		break;
	case StateCharacter:
		SDL_RenderClear(csdl_setup->renderer);
		SDL_RenderCopy(csdl_setup->renderer, selectCharacter_image, NULL, &imageRect);
		switch (event.key.keysym.sym) {
		case SDLK_1:
			SDL_RenderClear(csdl_setup->renderer);
			SDL_RenderCopy(csdl_setup->renderer, selectCharacter1, NULL, &imageRect);
			character = new MainCharacter(csdl_setup, "image/character1.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			break;

		case SDLK_2:
			SDL_RenderClear(csdl_setup->renderer);
			SDL_RenderCopy(csdl_setup->renderer, selectCharacter2, NULL, &imageRect);
			character = new MainCharacter(csdl_setup, "image/character2.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			break;

		case SDLK_3:
			SDL_RenderClear(csdl_setup->renderer);
			SDL_RenderCopy(csdl_setup->renderer, selectCharacter3, NULL, &imageRect);
			character = new MainCharacter(csdl_setup, "image/character3.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			break;

		case SDLK_4:
			SDL_RenderClear(csdl_setup->renderer);
			SDL_RenderCopy(csdl_setup->renderer, selectCharacter4, NULL, &imageRect);
			character = new MainCharacter(csdl_setup, "image/character4.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			break;

		case SDLK_5:
			SDL_RenderClear(csdl_setup->renderer);
			SDL_RenderCopy(csdl_setup->renderer, selectCharacter5, NULL, &imageRect);
			character = new MainCharacter(csdl_setup, "image/character5.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			break;

		case SDLK_6:
			SDL_RenderClear(csdl_setup->renderer);
			SDL_RenderCopy(csdl_setup->renderer, selectCharacter6, NULL, &imageRect);
			character = new MainCharacter(csdl_setup, "image/character6.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			break;

		case SDLK_7:
			SDL_RenderClear(csdl_setup->renderer);
			SDL_RenderCopy(csdl_setup->renderer, selectCharacter7, NULL, &imageRect);
			character = new MainCharacter(csdl_setup, "image/character7.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			break;

		case SDLK_8:
			SDL_RenderClear(csdl_setup->renderer);
			SDL_RenderCopy(csdl_setup->renderer, selectCharacter8, NULL, &imageRect);
			character = new MainCharacter(csdl_setup, "image/character8.png", &MouseX, &MouseY, &CameraX, &CameraY, ForestStage);
			break;

		case SDLK_9:
			SDL_RenderClear(csdl_setup->renderer);
			SDL_RenderCopy(csdl_setup->renderer, selectCharacter9, NULL, &imageRect);
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
	SDL_RenderPresent(csdl_setup->renderer);

}


void CMain::OnExecute() {
	while (!quit && csdl_setup->GetMainEvent()->type != SDL_QUIT) {
		OnGame();
		OnRender();
	}
}


