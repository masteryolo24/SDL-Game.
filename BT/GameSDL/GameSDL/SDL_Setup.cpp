#include "stdafx.h"
#include "SDL_Setup.h"

CSDL_Setup::CSDL_Setup(bool quit, int ScreenWidth, int ScreenHeight)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	window = NULL;
	window = SDL_CreateWindow("Create A World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "Can not create audio: " << Mix_GetError << std::endl;
	}


	if (window == NULL)
	{
		std::cout << "Can not create window:" << SDL_GetError << std::endl;
		quit = true;
	}
	iconSurface = IMG_Load("image/UET.ico");
	SDL_SetWindowIcon(window, iconSurface);

	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetCursor(cursor);

	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	mainEvent = new SDL_Event();


}

CSDL_Setup::~CSDL_Setup()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete mainEvent;
	SDL_FreeSurface(iconSurface);
	SDL_FreeCursor(cursor);
	Mix_CloseAudio();
}

SDL_Renderer* CSDL_Setup::GetRenderer() {
	return renderer;
}

SDL_Event* CSDL_Setup::GetMainEvent() {
	return mainEvent;
}

void CSDL_Setup::Begin() {
	SDL_PollEvent(mainEvent);
	SDL_RenderClear(renderer);
}

void CSDL_Setup::End() {
	SDL_RenderPresent(renderer);
}