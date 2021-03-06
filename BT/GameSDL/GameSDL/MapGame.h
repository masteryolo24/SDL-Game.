#pragma once
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Sprite.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Tree.h"
#include "WaterPic.h"
#include "MountainPic.h"
#include "CastlePic.h"
#include "FountainPic.h"
#include "SoilPic.h"
#include "WheatPic.h"
#include "TentPic.h"
#include "FlagPic.h"
#include "FirePic.h"
#include "MagicBook.h"
class CMapGame
{
public:
	CMapGame(int ScreenWidth, int ScreenHeight, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup);
	~CMapGame();

	void DrawBackGround();
	void DrawObject();
	void Update();
	void UpLoadStage();
	void SaveStage();

	enum ModeStage
	{
		GamePlay,
		Level,
		Delete,
		NonDelete
	};

	bool Magic;

	std::vector <Tree*> GetTrees() { return moreTrees; }
	std::vector <WaterPic*> GetWater() { return Waters; }
	std::vector <MountainPic*> GetMountain() { return Mountains; }
	std::vector <CastlePic*> GetCastle() { return Castles; }
	std::vector <FountainPic*> GetFountain() { return Fountains; }
	std::vector <SoilPic*> GetSoil() { return Soils; }
	std::vector <WheatPic*> GetWheat() { return Wheats; }
	std::vector <TentPic*> GetTent() { return Tents; }
	std::vector <FlagPic*> GetFlag() { return Flags; }
	std::vector <FirePic*> GetFire() { return Fires; }
	std::vector <MagicBook*> GetBook() { return Books; }

private:
	int Mode;
	int ModeDelete;

	CSDL_Setup* csdl_setup;


	float* CameraX;
	float* CameraY;

	int FireX[100], FireY[100];

	int BookX, BookY;

	int x, y;
	bool OnePressed;
	bool SavedGame;
	int FireCount;
	CSprite* grass;
	std::vector <Tree*> moreTrees;
	std::vector <WaterPic*> Waters;
	std::vector <MountainPic*> Mountains;
	std::vector <CastlePic*> Castles;
	std::vector <FountainPic*> Fountains;
	std::vector <SoilPic*> Soils;
	std::vector <WheatPic*> Wheats;
	std::vector <TentPic*> Tents;
	std::vector <FlagPic*> Flags;
	std::vector <FirePic*> Fires;
	std::vector <MagicBook*> Books;

	Mix_Chunk* putSound;
	Mix_Chunk* soundSelect;
	Mix_Chunk* soundSave;

	SDL_Texture* levelCreateON;
	SDL_Texture* levelCreateOFF;
	SDL_Texture* Saved;
	SDL_Rect levelRect;
	SDL_Rect savedRect;

	SDL_Texture* deleteCreateON;
	SDL_Texture* deleteCreateOFF;
	SDL_Rect deleteRect;
};

