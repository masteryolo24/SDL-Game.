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
class CMapGame
{
public:
	CMapGame(int ScreenWidth, int ScreenHeight, float *CameraX, float *CameraY, CSDL_Setup* csdl_setup);
	~CMapGame();

	void DrawBackGround();
	void DrawObject();
	void Update();

	void SaveStage();
	void UpLoadStage();

	enum ModeStage
	{
		GamePlay,
		Level,
		Delete,
		NonDelete
	};

	std::vector <Tree*> GetTrees() { return moreTrees; }
	std::vector <WaterPic*> GetWater() { return Waters; }
	std::vector <MountainPic*> GetMountain() { return Mountains; }
	std::vector <CastlePic*> GetCastle() { return Castles; }
	std::vector <FountainPic*> GetFountain() { return Fountains; }
	std::vector <SoilPic*> GetSoil() { return Soils; }
	std::vector <WheatPic*> GetWheat() { return Wheats; }
	std::vector <TentPic*> GetTent() { return Tents; }
	std::vector <FlagPic*> GetFlag() { return Flags; }

private:
	int Mode;
	int ModeDelete;

	CSDL_Setup* csdl_setup;
	float* CameraX;
	float* CameraY;

	bool OnePressed;
	bool SavedGame;
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

	Mix_Chunk* putSound;
	Mix_Chunk* soundSave;
	Mix_Chunk* soundSelect;

	SDL_Texture* levelCreateON;
	SDL_Texture* levelCreateOFF;
	SDL_Rect levelRect;

	SDL_Texture* deleteCreateON;
	SDL_Texture* deleteCreateOFF;
	SDL_Rect deleteRect;

	SDL_Texture* Saved;
	SDL_Rect savedRect;
};

