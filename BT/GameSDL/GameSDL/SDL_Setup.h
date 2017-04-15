#pragma once
class CSDL_Setup
{
public:
	CSDL_Setup(bool quit, int ScreenWidth, int ScreenHeight);
	~CSDL_Setup(void);

	SDL_Renderer* GetRenderer();
	SDL_Event* GetMainEvent();

	void Begin();
	void End();
	SDL_Renderer* renderer;
private:
	SDL_Window* window;

	SDL_Event* mainEvent;
	SDL_Surface* iconSurface;
	SDL_Cursor* cursor;
	SDL_Surface* cursorSurface;
};