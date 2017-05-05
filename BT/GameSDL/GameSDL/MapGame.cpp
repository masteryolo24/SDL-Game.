#include "MapGame.h"

CMapGame::CMapGame(int ScreenWidth, int ScreenHeight, float *passed_CameraX, float *passed_CameraY, CSDL_Setup* passed_csdl_setup)
{
	csdl_setup = passed_csdl_setup;
	CameraX = passed_CameraX;
	CameraY = passed_CameraY;
	
	grass = new CSprite(csdl_setup->GetRenderer(), "image/map/map.png", 0 , 0 , 4000, 3171, CameraX, CameraY, CCollisionDetection());
	Mode = Level;
	ModeDelete = NonDelete;
	OnePressed = false;

	levelCreateON = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/levelCreateON.png");
	levelCreateOFF = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/levelCreateOFF.png");
	deleteCreateON = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/deleteCreateON.png");
	deleteCreateOFF = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/deleteCreateOFF.png");

	levelRect.x = levelRect.y = deleteRect.y  = 0;
	levelRect.w = deleteRect.w =  300;
	levelRect.h = deleteRect.h =  35;
	deleteRect.x = 350;

	putSound = Mix_LoadWAV("sound/putSound.wav");
	soundSelect = Mix_LoadWAV("sound/clickSound.wav");
}

CMapGame::~CMapGame(void){

	delete grass;
	for (std::vector<Tree*>::iterator it = moreTrees.begin(); it != moreTrees.end(); ++it) {
		delete (*it);
	}
	moreTrees.clear();

	for (std::vector<WaterPic*>::iterator it = Waters.begin(); it != Waters.end(); ++it) {
		delete (*it);
	}
	Waters.clear();

	for (std::vector<MountainPic*>::iterator it = Mountains.begin(); it != Mountains.end(); ++it) {
		delete (*it);
	}
	Mountains.clear();

	for (std::vector<CastlePic*>::iterator it = Castles.begin(); it != Castles.end(); ++it) {
		delete (*it);
	}
	Castles.clear();

	for (std::vector<FountainPic*>::iterator it = Fountains.begin(); it != Fountains.end(); ++it) {
		delete (*it);
	}
	Fountains.clear();

	for (std::vector<SoilPic*>::iterator it = Soils.begin(); it != Soils.end(); ++it) {
		delete (*it);
	}
	Soils.clear();

	for (std::vector<WheatPic*>::iterator it = Wheats.begin(); it != Wheats.end(); ++it) {
		delete (*it);
	}
	Wheats.clear();

	for (std::vector<TentPic*>::iterator it = Tents.begin(); it != Tents.end(); ++it) {
		delete (*it);
	}
	Tents.clear();
	for (std::vector<FlagPic*>::iterator it = Flags.begin(); it != Flags.end(); ++it) {
		delete (*it);
	}


	Mix_FreeChunk(putSound);
	Mix_FreeChunk(soundSelect);

	SDL_DestroyTexture(levelCreateON);
	SDL_DestroyTexture(levelCreateOFF);
	SDL_DestroyTexture(deleteCreateON);
	SDL_DestroyTexture(deleteCreateOFF);
}

void CMapGame::DrawBackGround() {

	grass->Draw();

	for (std::vector<SoilPic*>::iterator it = Soils.begin(); it != Soils.end(); ++it) {
		(*it)->DrawSoil();
	}
}

void CMapGame::DrawObject() {
	for (std::vector <WheatPic*>::iterator it = Wheats.begin(); it != Wheats.end(); ++it) {
		(*it)->DrawWheat();
	}

	for (std::vector<WaterPic*>::iterator it = Waters.begin(); it != Waters.end(); ++it) {
		(*it)->DrawWater();
	}

	for (std::vector<Tree*>::iterator it = moreTrees.begin(); it != moreTrees.end(); ++it) {
		(*it)->DrawTrees();
	}

	for (std::vector<MountainPic*>::iterator it = Mountains.begin(); it != Mountains.end(); ++it) {
		(*it)->DrawMountain();
	}

	for (std::vector<CastlePic*>::iterator it = Castles.begin(); it != Castles.end(); ++it) {
		(*it)->DrawCastle();
	}

	for (std::vector<FountainPic*>::iterator it = Fountains.begin(); it != Fountains.end(); ++it) {
		(*it)->DrawFountain();
	}
	for (std::vector<TentPic*>::iterator it = Tents.begin(); it != Tents.end(); ++it) {
		(*it)->DrawTent();
	}
	for (std::vector<FlagPic*>::iterator it = Flags.begin(); it != Flags.end(); ++it) {
		(*it)->DrawFlag();
	}

	if (Mode == GamePlay && (ModeDelete == NonDelete || ModeDelete == Delete))
		SDL_RenderCopy(csdl_setup->GetRenderer(), levelCreateOFF, NULL, &levelRect);
	if (Mode == Level && (ModeDelete == NonDelete || ModeDelete == Delete))
		SDL_RenderCopy(csdl_setup->GetRenderer(), levelCreateON, NULL, &levelRect);
	if (ModeDelete == NonDelete && (Mode == GamePlay || Mode == Level))
		SDL_RenderCopy(csdl_setup->GetRenderer(), deleteCreateOFF, NULL, &deleteRect);
	if (ModeDelete == Delete && (Mode == GamePlay || Mode == Level))
		SDL_RenderCopy(csdl_setup->GetRenderer(), deleteCreateON, NULL, &deleteRect);
}

void CMapGame::Update() {
	if (Mode == Level){
		if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN) {
			if (!OnePressed) {
				switch (csdl_setup->GetMainEvent()->key.keysym.sym) {
				case SDLK_1: 
					Mix_PlayChannel(1, putSound, 0);
					moreTrees.push_back(new Tree(-*CameraX + 480, -*CameraY + 170, CameraX, CameraY, csdl_setup));
					OnePressed = true;
					break;
				
				case SDLK_2: 
					Mix_PlayChannel(1, putSound, 0);
					Waters.push_back(new WaterPic(-*CameraX + 560, -*CameraY + 250, CameraX, CameraY, csdl_setup));
					OnePressed = true;
					break;
				
				case SDLK_3: 
					Mix_PlayChannel(1, putSound, 0);
					Mountains.push_back(new MountainPic(-*CameraX + 540, -*CameraY + 55, CameraX, CameraY, csdl_setup));
					OnePressed = true;
					break;
				
				case SDLK_4: 
					Mix_PlayChannel(1, putSound, 0);
					Castles.push_back(new CastlePic(-*CameraX + 540, -*CameraY + 120, CameraX, CameraY, csdl_setup));
					OnePressed = true;
					break;
				
				case SDLK_5: 
					Mix_PlayChannel(1, putSound, 0);
					Fountains.push_back(new FountainPic(-*CameraX + 540, -*CameraY + 230, CameraX, CameraY, csdl_setup));
					OnePressed = true;
					break;

				case SDLK_6:
					Mix_PlayChannel(1, putSound, 0);
					Soils.push_back(new SoilPic(-*CameraX + 520, -*CameraY + 230, CameraX, CameraY, csdl_setup));
					OnePressed = true;
					break;

				case SDLK_7:
					Mix_PlayChannel(1, putSound, 0);
					Wheats.push_back(new WheatPic(-*CameraX + 520, -*CameraY + 240, CameraX, CameraY, csdl_setup));
					OnePressed = true;
					break;
					
				case SDLK_8:
					Mix_PlayChannel(1, putSound, 0);
					Tents.push_back(new TentPic(-*CameraX + 550, -*CameraY + 240, CameraX, CameraY, csdl_setup));
					OnePressed = true;
					break;
				case SDLK_9:
					Mix_PlayChannel(1, putSound, 0);
					Flags.push_back(new FlagPic(-*CameraX + 520, -*CameraY + 240, CameraX, CameraY, csdl_setup));
					OnePressed = true;
					break;
				}
				Mix_Volume(1, 10);
			}

		}




	if (csdl_setup->GetMainEvent()->type == SDL_KEYUP) {
		if (OnePressed) {
			switch (csdl_setup->GetMainEvent()->key.keysym.sym) {
			case SDLK_1: 
				OnePressed = false;
				break;
			
			case SDLK_2: 
				OnePressed = false;
				break;
			
			case SDLK_3: 
				OnePressed = false;
				break;
			
			case SDLK_4: 
				OnePressed = false;
				break;
			
			case SDLK_5: 
				OnePressed = false;
				break;

			case SDLK_6:
				OnePressed = false;
				break;
			
			case SDLK_7:
				OnePressed = false;
				break;

			case SDLK_8:
				OnePressed = false;
				break;

			case SDLK_9:
				OnePressed = false;
				break;
			}

		}
	}
}


	if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN) {
		if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_TAB) {
			if (Mode == Level && ModeDelete == NonDelete) {
				Mix_PlayChannel(3, soundSelect, 0);
				std::cout << "Level Creation OFF!" << std::endl;
				Mode = GamePlay;
			}
			else if (Mode == GamePlay && ModeDelete == NonDelete)
			{
				Mix_PlayChannel(3, soundSelect, 0);
				std::cout << "Level Creation ON!" << std::endl;
				Mode = Level;
			}
			OnePressed = true;
		}
	}

	if (csdl_setup->GetMainEvent()->type == SDL_KEYUP) {
		if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_TAB) {
			OnePressed = false;
		}
	}


	if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN) {
		if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_d) {
			if (Mode == GamePlay && ModeDelete == NonDelete) {
				Mix_PlayChannel(3, soundSelect, 0);
				std::cout << "Delete Creation ON!" << std::endl;
				ModeDelete = Delete;
			}
			else if (Mode == GamePlay && ModeDelete == Delete)
			{
				Mix_PlayChannel(3, soundSelect, 0);
				std::cout << "Delete Creation OFF!" << std::endl;
				ModeDelete = NonDelete;
			}
			OnePressed = true;
		}
	}

	if (csdl_setup->GetMainEvent()->type == SDL_KEYUP) {
		if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_d) {
			OnePressed = false;
		}
	}

	///================DELETE MODE ON=============///

	if (ModeDelete == Delete) {
		if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN) {
			if (!OnePressed) {
				switch (csdl_setup->GetMainEvent()->key.keysym.sym) {

					///============== DELETE TREE ================///

				case SDLK_1:
					if (moreTrees.size() > 0) {
						delete moreTrees[moreTrees.size() - 1];
						moreTrees.pop_back();
					}
					break;
				

				///================= DELETE WATER ================///

				case SDLK_2:
					if (Waters.size() > 0) {
						delete Waters[Waters.size() - 1];
						Waters.pop_back();
					}
					break;
				

				///==============DELETE MOUNTAIN=============///

				case SDLK_3:
					if (Mountains.size() > 0) {
						delete Mountains[Mountains.size() - 1];
						Mountains.pop_back();
					}
					break;
				

				///==============DELETE CASTLE=============///

				case SDLK_4:
					if (Castles.size() > 0) {
						delete Castles[Castles.size() - 1];
						Castles.pop_back();
					}
					break;
				

				///===========DELETE FOUNTAIN===========///

				case SDLK_5:
					if (Fountains.size() > 0) {
						delete Fountains[Fountains.size() - 1];
						Fountains.pop_back();
					}
					break;
				
					///============== DELETE SOIL ================///

				case SDLK_6:
					if (Soils.size() > 0) {
						delete Soils[Soils.size() - 1];
						Soils.pop_back();
					}
					break;
					///=================
				case SDLK_7:
					if (Wheats.size() > 0) {
						delete Wheats[Wheats.size() - 1];
						Wheats.pop_back();
					}
					break;
					///===========DELETE TENT============///
				case SDLK_8:
					if (Tents.size() > 0) {
						delete Tents[Tents.size() - 1];
						Tents.pop_back();
					}
					break;
					///===========

				case SDLK_9:
					if (Flags.size() > 0) {
						delete Flags[Flags.size() - 1];
						Flags.pop_back();
					}
					break;
				}
			}
		}

		if (csdl_setup->GetMainEvent()->type == SDL_KEYUP) {
			if (OnePressed) {
				switch (csdl_setup->GetMainEvent()->key.keysym.sym) {
				case SDLK_1:
					OnePressed = false;
					break;

				case SDLK_2:
					OnePressed = false;
					break;

				case SDLK_3:
					OnePressed = false;
					break;

				case SDLK_4:
					OnePressed = false;
					break;

				case SDLK_5:
					OnePressed = false;
					break;

				case SDLK_6:
					OnePressed = false;
					break;

				case SDLK_7:
					OnePressed = false;
					break;
				case SDLK_8:
					OnePressed = false;
					break;
				case SDLK_9:
					OnePressed = false;
					break;
				}

			}
		}
	}
}