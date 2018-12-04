#include "GameController.h"
//#define FPS 60

namespace gameEngine {

	GameController::GameController() {
		SDL_Init(SDL_INIT_EVERYTHING);

		int flags = IMG_INIT_PNG;
		int initted = IMG_Init(flags);
		if ((initted&flags) != flags) {
			std::cout << "IMG_Init: Failed to init required png support!\n" << std::endl;
			std::cout << "IMG_Init: %s\n" << IMG_GetError() << std::endl;
		}

		win = SDL_CreateWindow("Game", 100, 100, 640, 640, 0);
		ren = SDL_CreateRenderer(win, -1, 0);

	}

	/*void GameController::eventHandler() {
		const int tickInterval = 1000 / FPS;
		bool running = true;
		while (running) {
			Uint32 nextTick = SDL_GetTicks() + tickInterval;
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT: running = false; break;
				case SDL_MOUSEBUTTONDOWN: {
					mouseClick(&event.button);
				} break;
				}
			}
			renderReset();
			int delay = nextTick - SDL_GetTicks();
			if (delay > 0)
				SDL_Delay(delay);
		}
	}

	void GameController::mouseClick(SDL_MouseButtonEvent* mb) {
		SDL_Point p = { mb->x, mb->y };
		SDL_Rect* r = checkPoint(&p);
		if (mb->button == SDL_BUTTON_RIGHT) {
			if (r != nullptr)
				player->moving(r);
		}
		else if (mb->button == SDL_BUTTON_LEFT) {
			if (r != nullptr)
				player->shoot(r);
		}
	}

	SDL_Rect* GameController::checkPoint(SDL_Point* p) {
		for (auto& b : bg) {
			if (SDL_PointInRect(p, b.second->getRect())) {
				return b.second->getRect();
			}
		}
		return nullptr;
	}*/

	void GameController::renderReset() {
		for (auto& co1 : collObjs) {
			for (auto& co2 : collObjs) {
				if (co1 != co2) {
					co1.second->checkCollision(co2.second);
				}
			}
		}
		SDL_RenderClear(ren);
		for (auto& bg : bgs) {
			bg.second->tick();
		}
		for (auto& co : collObjs) {
			co.second->tick();
		}
		SDL_RenderPresent(ren);
	}

	void GameController::addBackground(const char* path, std::string name, int x, int y, int sizeX, int sizeY) {
		Background* bg = Background::getInstance(path, name, x, y, sizeX, sizeY);
		bgs.emplace(name, bg);
	}

	Character* GameController::addCharacter(int pHealth, double pSpeed, const char* path, std::string name, int x, int y, int sizeX, int sizeY) {
		Character* character = Character::getInstance(pHealth, pSpeed, path, name, x, y, sizeX, sizeY);
		collObjs.emplace(name, character);
		return character;
	}

	void GameController::createBG(int amount, const char* path) {
		std::string name = "background0";
		char c = '0';
		int posX = 0, posY = 0, total = 0;
		for (int i = 0; i < amount; i++) {
			name.replace(10, 1, &c);
			c++;
			addBackground(path, name, posX, posY);
			posX += 64;
			if (posX == 640) {
				posX = 0;
				posY += 64;
			}
		}
	}

	SDL_Renderer* GameController::getRen() {
		return ren;
	}

	std::unordered_map<std::string, CollisionSprite*>* GameController::getCollidingObjects() {
		return &collObjs;
	}

	std::unordered_map<std::string, Background*>* GameController::getBackgrounds() {
		return &bgs;
	}

	void GameController::removeCollidingObject(std::string n) {
		collObjs.erase(n);
	}

	void GameController::removeBackground(std::string n) {
		bgs.erase(n);
	}

	GameController::~GameController() {
		bgs.clear();
		collObjs.clear();
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
	}

	GameController gc;

}