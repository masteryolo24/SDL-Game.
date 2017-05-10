#include "MapGame.h"

CMapGame::CMapGame(int ScreenWidth, int ScreenHeight, float *passed_CameraX, float *passed_CameraY, CSDL_Setup* passed_csdl_setup)
{
	srand(time(NULL));
	csdl_setup = passed_csdl_setup;
	CameraX = passed_CameraX;
	CameraY = passed_CameraY;

	grass = new CSprite(csdl_setup->GetRenderer(), "image/map/map.png", 0, 0, 4000, 3171, CameraX, CameraY, CCollisionDetection());
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
	for (int i = 0; i < 40; i++) {
		FireX[i] = rand() % 3700;
		FireY[i] = rand() % 2500;
		Fires.push_back(new FirePic(FireX[i], FireY[i], CameraX, CameraY, csdl_setup));
	}
	BookX = rand() % 100;
	BookY = rand() % 100;
	Books.push_back(new MagicBook(BookX, BookY, CameraX, CameraY, csdl_setup));
}

CMapGame::~CMapGame(void) {

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

	for (std::vector< FirePic*>::iterator it = Fires.begin(); it != Fires.end(); ++it) {
		delete (*it);
	}

	for (std::vector<MagicBook*>::iterator it = Books.begin(); it != Books.end(); ++it) {
		delete (*it);
	}

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
	for (std::vector<FlagPic*>::iterator it = Flags.begin(); it != Flags.end(); ++it) {
		(*it)->DrawFlag();
	}
	for (std::vector <FirePic*>::iterator it = Fires.begin(); it != Fires.end(); ++it) {
		(*it)->DrawFire();
	}

	for (std::vector <MagicBook*>::iterator it = Books.begin(); it != Books.end(); ++it) {
		(*it)->DrawBook();
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
	std::fstream LoadStage("Saved/Map.txt");
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
		TypeTent,
		TypeFlag
	};
	int TypeObject = TypeNone;
	if (LoadStage.is_open()) {
		while (LoadStage.good())
		{
			std::getline(LoadStage, line);

			///================Tree Position===========///
			if (line == "Tree Position--") {
				TypeObject = TypeTree;
			}
			else if (line == "--Tree Position") {
				TypeObject = TypeNone;
			}
			else {
				if (TypeObject == TypeTree) {
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
				TypeObject = TypeWater;
			}
			else if (line == "--Water Position") {
				TypeObject = TypeNone;
			}
			else {
				if (TypeObject == TypeWater) {
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
				TypeObject = TypeMountain;
			}
			else if (line == "--Mountain Position") {
				TypeObject = TypeNone;
			}
			else {
				if (TypeObject == TypeMountain) {
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
				TypeObject = TypeCastle;
			}
			else if (line == "--Castle Position") {
				TypeObject = TypeNone;
			}
			else {
				if (TypeObject == TypeCastle) {
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
				TypeObject = TypeFountain;
			}
			else if (line == "--Fountain Position") {
				TypeObject = TypeNone;
			}
			else {
				if (TypeObject == TypeFountain) {
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
				TypeObject = TypeSoil;
			}
			else if (line == "--Soil Position") {
				TypeObject = TypeNone;
			}
			else {
				if (TypeObject == TypeSoil) {
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
				TypeObject = TypeWheat;
			}
			else if (line == "--Wheat Position") {
				TypeObject = TypeNone;
			}
			else {
				if (TypeObject == TypeWheat) {
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
				TypeObject = TypeTent;
			}
			else if (line == "--Tent Position") {
				TypeObject = TypeTent;
			}
			else {
				if (TypeObject == TypeTent) {
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
			if (line == "Flag Position--") {
				TypeObject = TypeFlag;
			}
			else if (line == "--Flag Position") {
				TypeObject = TypeFlag;
			}
			else {
				if (TypeObject == TypeFlag) {
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
							Flags.push_back(new FlagPic(TempX, TempY, CameraX, CameraY, csdl_setup));
						}
						FirstWord = word;
					}
				}
			}
			///================
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
	///===============SAVE Flag Position==========///
	LoadStage << "Flag Position--" << std::endl;
	for (std::vector<FlagPic*>::iterator it = Flags.begin(); it < Flags.end(); ++it) {
		LoadStage << "x: " << (*it)->GetX() << "\ty: " << (*it)->GetY() << std::endl;
	}
	LoadStage << "--Flag Position" << std::endl;
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

	if (Mode == Level) {
		for (std::vector<WaterPic*>::iterator it = Waters.begin(); it != Waters.end(); ++it) {
			(*it)->GetX();
		}
		if (Fires.size() == 0) {
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
						Waters.push_back(new WaterPic(-*CameraX + 540, -*CameraY + 250, CameraX, CameraY, csdl_setup));
						OnePressed = true;
						break;

					case SDLK_3:
						Mix_PlayChannel(1, putSound, 0);
						Mountains.push_back(new MountainPic(-*CameraX + 520, -*CameraY + 55, CameraX, CameraY, csdl_setup));
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
	if (Magic == true) {
		if (Books.size() > 0) {
			delete Books[Books.size() - 1];
			Books.pop_back();
		}
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

					case SDLK_SPACE:
						if (Fires.size() > 0) {
							delete Fires[Fires.size() - 1];
							Fires.pop_back();
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
					case SDLK_SPACE:
						OnePressed = false;
						break;
					}

				}
			}
		}
	}
}
