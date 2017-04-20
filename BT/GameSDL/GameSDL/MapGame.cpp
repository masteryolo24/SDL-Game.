#include "MapGame.h"

CMapGame::CMapGame(int ScreenWidth, int ScreenHeight, float *passed_CameraX, float *passed_CameraY, CSDL_Setup* passed_csdl_setup)
{
	csdl_setup = passed_csdl_setup;
	CameraX = passed_CameraX;
	CameraY = passed_CameraY;
	
	grass = new CSprite(csdl_setup->GetRenderer(), "image/map/map.png", 0 , 0 , 4000, 3171, CameraX, CameraY, CCollisionDetection());
	Mode = Level;
	ModeDelete = NonDelete;
	UpLoadStage();
	OnePressed = false;

	levelCreateON = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/levelCreateON.png");
	levelCreateOFF = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/levelCreateOFF.png");
	deleteCreateON = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/deleteCreateON.png");
	deleteCreateOFF = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/deleteCreateOFF.png");
	Saved = IMG_LoadTexture(csdl_setup->GetRenderer(), "image/savedGame.png");

	levelRect.x = levelRect.y = deleteRect.y = savedRect.y = 0;
	levelRect.w = deleteRect.w = savedRect.w = 300;
	levelRect.h = deleteRect.h = savedRect.h = 35;
	deleteRect.x = 350;
	savedRect.x = 900;

	putSound = Mix_LoadWAV("sound/putSound.wav");
	soundSelect = Mix_LoadWAV("sound/clickSound.wav");
	soundSave = Mix_LoadWAV("sound/savedGame.wav");
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


	Mix_FreeChunk(putSound);
	Mix_FreeChunk(soundSave);
	Mix_FreeChunk(soundSelect);

	SDL_DestroyTexture(levelCreateON);
	SDL_DestroyTexture(levelCreateOFF);
	SDL_DestroyTexture(deleteCreateON);
	SDL_DestroyTexture(deleteCreateOFF);
	SDL_DestroyTexture(Saved);
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

	if (Mode == GamePlay && (ModeDelete == NonDelete || ModeDelete == Delete))
		SDL_RenderCopy(csdl_setup->GetRenderer(), levelCreateOFF, NULL, &levelRect);
	if (Mode == Level && (ModeDelete == NonDelete || ModeDelete == Delete))
		SDL_RenderCopy(csdl_setup->GetRenderer(), levelCreateON, NULL, &levelRect);
	if (ModeDelete == NonDelete && (Mode == GamePlay || Mode == Level))
		SDL_RenderCopy(csdl_setup->GetRenderer(), deleteCreateOFF, NULL, &deleteRect);
	if (ModeDelete == Delete && (Mode == GamePlay || Mode == Level))
		SDL_RenderCopy(csdl_setup->GetRenderer(), deleteCreateON, NULL, &deleteRect);
	if (SavedGame == true)
		SDL_RenderCopy(csdl_setup->GetRenderer(), Saved, NULL, &savedRect);
}

void CMapGame::UpLoadStage() {
	std::ifstream LoadStage("Saved/Map.txt");
	std::string line;

	enum ObjectOther {
		TypeNone,
		TypeTree,
		TypeWater,
		TypeMountain,
		TypeCastle,
		TypeFountain,
		TypeSoil,
		TypeWheat,
		TypeTent
	};
	int CurrentOther = TypeNone;
	if (LoadStage.is_open()) {
		while (LoadStage.good())
		{
			std::getline(LoadStage, line);

			///================Tree Position===========///
			if (line == "Tree Position--") {
				CurrentOther = TypeTree;
			}
			else if (line == "--Tree Position") {
				CurrentOther = TypeNone;
			}
			else {
				if (CurrentOther == TypeTree) {
					std::istringstream iss(line);

					int TempX = 0;
					int TempY = 0;
					std::string FirstWord = "";

					while (iss)
					{
						std::string word;
						iss >> word;
						if (FirstWord == "x:") {
							TempX = atoi(word.c_str());
						}
						if (FirstWord == "y:") {
							TempY = atoi(word.c_str());
							moreTrees.push_back(new Tree(TempX, TempY, CameraX, CameraY, csdl_setup));
						}
						FirstWord = word;
					}
				}
			}
			///================LOAD Water Position==============///
			if (line == "Water Position--") {
				CurrentOther = TypeWater;
			}
			else if (line == "--Water Position") {
				CurrentOther = TypeNone;
			}
			else {
				if (CurrentOther == TypeWater) {
					std::istringstream iss(line);

					int TempX = 0;
					int TempY = 0;
					std::string FirstWord = "";

					while (iss)
					{
						std::string word;
						iss >> word;
						if (FirstWord == "x:") {
							TempX = atoi(word.c_str());
						}
						if (FirstWord == "y:") {
							TempY = atoi(word.c_str());
							Waters.push_back(new WaterPic(TempX, TempY, CameraX, CameraY, csdl_setup));
						}
						FirstWord = word;
					}
				}
			}
			///=============LOAD Mountain Position=============///
			if (line == "Mountain Position--") {
				CurrentOther = TypeMountain;
			}
			else if (line == "--Mountain Position") {
				CurrentOther = TypeNone;
			}
			else {
				if (CurrentOther == TypeMountain) {
					std::istringstream iss(line);

					int TempX = 0;
					int TempY = 0;
					std::string FirstWord = "";

					while (iss)
					{
						std::string word;
						iss >> word;
						if (FirstWord == "x:") {
							TempX = atoi(word.c_str());
						}
						if (FirstWord == "y:") {
							TempY = atoi(word.c_str());
							Mountains.push_back(new MountainPic(TempX, TempY, CameraX, CameraY, csdl_setup));
						}
						FirstWord = word;
					}
				}
			}

			///=============LOAD Castle Position=============///

			if (line == "Castle Position--") {
				CurrentOther = TypeCastle;
			}
			else if (line == "--Castle Position") {
				CurrentOther = TypeNone;
			}
			else {
				if (CurrentOther == TypeCastle) {
					std::istringstream iss(line);

					int TempX = 0;
					int TempY = 0;
					std::string FirstWord = "";

					while (iss)
					{
						std::string word;
						iss >> word;
						if (FirstWord == "x:") {
							TempX = atoi(word.c_str());
						}
						if (FirstWord == "y:") {
							TempY = atoi(word.c_str());
							Castles.push_back(new CastlePic(TempX, TempY, CameraX, CameraY, csdl_setup));
						}
						FirstWord = word;
					}
				}
			}
			///==============LOAD Fountain POSITION===============///

			if (line == "Fountain Position--") {
				CurrentOther = TypeFountain;
			}
			else if (line == "--Fountain Position") {
				CurrentOther = TypeNone;
			}
			else {
				if (CurrentOther == TypeFountain) {
					std::istringstream iss(line);

					int TempX = 0;
					int TempY = 0;
					std::string FirstWord = "";

					while (iss)
					{
						std::string word;
						iss >> word;
						if (FirstWord == "x:") {
							TempX = atoi(word.c_str());
						}
						if (FirstWord == "y:") {
							TempY = atoi(word.c_str());
							Fountains.push_back(new FountainPic(TempX, TempY, CameraX, CameraY, csdl_setup));
						}
						FirstWord = word;
					}
				}
			}
			///=======================LOAD Soil Position===============///
			if (line == "Soil Position--") {
				CurrentOther = TypeSoil;
			}
			else if (line == "--Soil Position") {
				CurrentOther = TypeNone;
			}
			else {
				if (CurrentOther == TypeSoil) {
					std::istringstream iss(line);

					int TempX = 0;
					int TempY = 0;
					std::string FirstWord = "";

					while (iss)
					{
						std::string word;
						iss >> word;
						if (FirstWord == "x:") {
							TempX = atoi(word.c_str());
						}
						if (FirstWord == "y:") {
							TempY = atoi(word.c_str());
							Soils.push_back(new SoilPic(TempX, TempY, CameraX, CameraY, csdl_setup));
						}
						FirstWord = word;
					}
				}
			}
			///======================LOAD Wheat Position==============///
			if (line == "Wheat Position--") {
				CurrentOther = TypeWheat;
			}
			else if (line == "--Wheat Position") {
				CurrentOther = TypeNone;
			}
			else {
				if (CurrentOther == TypeWheat) {
					std::istringstream iss(line);

					int TempX = 0;
					int TempY = 0;
					std::string FirstWord = "";

					while (iss)
					{
						std::string word;
						iss >> word;
						if (FirstWord == "x:") {
							TempX = atoi(word.c_str());
						}
						if (FirstWord == "y:") {
							TempY = atoi(word.c_str());
							Wheats.push_back(new WheatPic(TempX, TempY, CameraX, CameraY, csdl_setup));
						}
						FirstWord = word;
					}
				}
			}
			///===========LOAD Tent Position============///
			if (line == "Tent Position--") {
				CurrentOther = TypeTent;
			}
			else if (line == "--Tent Position") {
				CurrentOther = TypeTent;
			}
			else {
				if (CurrentOther == TypeTent) {
					std::istringstream iss(line);

					int TempX = 0;
					int TempY = 0;
					std::string FirstWord = "";

					while (iss)
					{
						std::string word;
						iss >> word;
						if (FirstWord == "x:") {
							TempX = atoi(word.c_str());
						}
						if (FirstWord == "y:") {
							TempY = atoi(word.c_str());
							Tents.push_back(new TentPic(TempX, TempY, CameraX, CameraY, csdl_setup));
						}
						FirstWord = word;
					}
				}
			}
			///=========
		}
	}
	else {
		std::cout << "You didn't save stage" << std::endl;
	}
}

void CMapGame::SaveStage() {
	std::ofstream LoadStage;
	LoadStage.open("Saved/Map.txt");
	///==========SAVE Tree Position==============///
	LoadStage << "Tree Position--" << std::endl;
	for (std::vector<Tree*>::iterator it = moreTrees.begin(); it < moreTrees.end(); ++it) {
		LoadStage << "x: " << (*it)->GetX() << "\ty: " << (*it)->GetY() << std::endl;
	}
	LoadStage << "--Tree Position" << std::endl;

	///===============SAVE Water Position===========///
	LoadStage << "Water Position--" << std::endl;
	for (std::vector<WaterPic*>::iterator it = Waters.begin(); it < Waters.end(); ++it) {
		LoadStage << "x: " << (*it)->GetX() << "\ty: " << (*it)->GetY() << std::endl;
	}
	LoadStage << "--Water Position" << std::endl;

	///===========SAVE Mountain Position===============///
	LoadStage << "Mountain Position--" << std::endl;
	for (std::vector<MountainPic*>::iterator it = Mountains.begin(); it < Mountains.end(); ++it) {
		LoadStage << "x: " << (*it)->GetX() << "\ty: " << (*it)->GetY() << std::endl;
	}
	LoadStage << "--Mountain Position" << std::endl;

	///==========SAVE Castle Position==============///
	LoadStage << "Castle Position--" << std::endl;
	for (std::vector<CastlePic*>::iterator it = Castles.begin(); it < Castles.end(); ++it) {
		LoadStage << "x: " << (*it)->GetX() << "\ty: " << (*it)->GetY() << std::endl;
	}
	LoadStage << "--Castle Position" << std::endl;

	///===========SAVE Fountain Position=========///
	LoadStage << "Fountain Position--" << std::endl;
	for (std::vector<FountainPic*>::iterator it = Fountains.begin(); it < Fountains.end(); ++it) {
		LoadStage << "x: " << (*it)->GetX() << "\ty: " << (*it)->GetY() << std::endl;
	}
	LoadStage << "--Fountain Position" << std::endl;
	///==========SAVE Soil Position=============///
	LoadStage << "Soil Position--" << std::endl;
	for (std::vector<SoilPic*>::iterator it = Soils.begin(); it < Soils.end(); ++it) {
		LoadStage << "x: " << (*it)->GetX() << "\ty: " << (*it)->GetY() << std::endl;
	}
	LoadStage << "--Soil Position" << std::endl;
	///==========SAVE Wheat Position==============///
	LoadStage << "Wheat Position--" << std::endl;
	for (std::vector<WheatPic*>::iterator it = Wheats.begin(); it < Wheats.end(); ++it) {
		LoadStage << "x: " << (*it)->GetX() << "\ty: " << (*it)->GetY() << std::endl;
	}
	LoadStage << "--Wheat Position" << std::endl;
	///===============

	LoadStage.close();
	std::cout << "Level Save!" << std::endl;
}

void CMapGame::Update() {
	if ((Mode == Level || Mode == GamePlay) && ModeDelete == NonDelete) {
		if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN) {
			if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_s) {
				Mix_PlayChannel(2, soundSave, 0);
				Mix_Volume(2, 20);
				SaveStage();
				OnePressed = true;
				SavedGame = true;
			}
		}
	}


	if (csdl_setup->GetMainEvent()->type == SDL_KEYUP) {
		if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_s) {
			OnePressed = false;
			SavedGame = false;
		}
	}

	if (Mode == Level){
		if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN) {
			if (!OnePressed) {
				switch (csdl_setup->GetMainEvent()->key.keysym.sym) {
				case SDLK_1: 
					Mix_PlayChannel(1, putSound, 0);
					moreTrees.push_back(new Tree(-*CameraX + 280, -*CameraY + 120, CameraX, CameraY, csdl_setup));
					OnePressed = true;
					break;
				
				case SDLK_2: 
					Mix_PlayChannel(1, putSound, 0);
					Waters.push_back(new WaterPic(-*CameraX + 330, -*CameraY + 200, CameraX, CameraY, csdl_setup));
					OnePressed = true;
					break;
				
				case SDLK_3: 
					Mix_PlayChannel(1, putSound, 0);
					Mountains.push_back(new MountainPic(-*CameraX + 320, -*CameraY + 5, CameraX, CameraY, csdl_setup));
					OnePressed = true;
					break;
				
				case SDLK_4: 
					Mix_PlayChannel(1, putSound, 0);
					Castles.push_back(new CastlePic(-*CameraX + 320, -*CameraY + 70, CameraX, CameraY, csdl_setup));
					OnePressed = true;
					break;
				
				case SDLK_5: 
					Mix_PlayChannel(1, putSound, 0);
					Fountains.push_back(new FountainPic(-*CameraX + 320, -*CameraY + 180, CameraX, CameraY, csdl_setup));
					OnePressed = true;
					break;

				case SDLK_6:
					Mix_PlayChannel(1, putSound, 0);
					Soils.push_back(new SoilPic(-*CameraX + 320, -*CameraY + 180, CameraX, CameraY, csdl_setup));
					OnePressed = true;
					break;

				case SDLK_7:
					Mix_PlayChannel(1, putSound, 0);
					Wheats.push_back(new WheatPic(-*CameraX + 320, -*CameraY + 190, CameraX, CameraY, csdl_setup));
					OnePressed = true;
					break;
					
				case SDLK_8:
					Mix_PlayChannel(1, putSound, 0);
					Tents.push_back(new TentPic(-*CameraX + 320, -*CameraY + 190, CameraX, CameraY, csdl_setup));
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
			}

		}
	}
}

	///================= CREATE LEVEL MODE ================///

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

	///============== CREATE DELETE MODE ================///


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
				}

			}
		}
	}
}