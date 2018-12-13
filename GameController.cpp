#include "GameController.h"

#define FPS 60

namespace gameEngine {

	GameController::GameController() {
		sys = System::getInstance();
	}

	GameController* GameController::getInstance() {
		return new GameController();
	}

	System* GameController::getSys() {
		return sys;
	}

	void GameController::start() {
		for (auto& co : collObjs) {
			co->createColliders();
		}
		eventHandler();
	}

	void GameController::renderReset() {
		//sys->getRenderStart() = SDL_GetTicks();
		for (auto& co1 : collObjs) {
			for (auto& co2 : collObjs) {
				if (co1 != co2) {
					co1->checkCollision(co2);
				}
			}
		}
		SDL_RenderClear(sys->getRen());
		for (auto& bg : bgs) {
			bg->tick();
		}
		for (auto& co : collObjs) {
			co->tick();
		}
		SDL_RenderPresent(sys->getRen());
	}

	void GameController::addBackground(const char* path, std::string name, int x, int y, int sizeX, int sizeY) {
		Background* bg = Background::getInstance(path, name, x, y, sizeX, sizeY);
		bgs.push_back(bg);
	}

	Character* GameController::addCharacter(int pHealth, int pSpeed, const char* path, std::string name, int x, int y, int sizeX, int sizeY) {
		Character* character = Character::getInstance(pHealth, pSpeed, path, name, x, y, sizeX, sizeY);
		collObjs.push_back(character);
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

	std::vector<CollisionSprite*>* GameController::getCollidingObjects() {
		return &collObjs;
	}

	std::vector<Background*>* GameController::getBackgrounds() {
		return &bgs;
	}

	void GameController::removeCollidingObject(CollisionSprite* n) {
		removeCollObjs.push_back(n);
	}

	void GameController::removeBackground(Background* n) {
		removeBgs.push_back(n);
	}

	void GameController::removeObjects() {
		for (CollisionSprite* cs : removeCollObjs) {
			for (std::vector<CollisionSprite*>::iterator i = collObjs.begin(); i != collObjs.end(); )
				if (*i == cs) {
					i = collObjs.erase(i);
					delete cs;
				}
				else
					i++;
		}
		removeCollObjs.clear();

		for (Background* bg : removeBgs) {
			for (std::vector<Background*>::iterator i = bgs.begin(); i != bgs.end(); )
				if (*i == bg) {
					i = bgs.erase(i);
					delete bg;
				}
				else
					i++;
		}
		removeBgs.clear();
	}

	void GameController::setPlayer(Character* p) {
		player = p;
	}

	Character* GameController::getPlayer() {
		return player;
	}

	void GameController::eventHandler() {
		const int tickInterval = 1000 / FPS;
		running = true;
		while (running) {
			Uint32 nextTick = SDL_GetTicks() + tickInterval;
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT: running = false; break;
				case SDL_MOUSEBUTTONDOWN: {
					mouseDown(&event.button);
				} break;
				case SDL_KEYDOWN: {
					keyDown(&event.key.keysym.sym);
				} break;
				}
			}
			removeObjects();
			renderReset();
			int delay = nextTick - SDL_GetTicks();
			if (delay > 0)
				SDL_Delay(delay);
		}
	}

	void GameController::mouseDown(SDL_MouseButtonEvent* mb) {
		SDL_Point point = { mb->x, mb->y };
		p = &point;
		switch (mb->button) {
		case SDL_BUTTON_RIGHT:
			rightMB();
			break;
		case SDL_BUTTON_LEFT:
			leftMB();
			break;
		}
		
	}

	void GameController::keyDown(SDL_Keycode* key) {
		switch (*key) {
		case SDLK_ESCAPE:
			keyEscape();
			break;
		}
	}

	void GameController::SetRightMouseButton(void(*function)()) {
		rightMB = function;
	}

	void GameController::SetLeftMouseButton(void(*function)()) {
		leftMB = function;
	}

	void GameController::SetEscapeKey(void(*function)()) {
		keyEscape = function;
	}

	void GameController::quit() {
		running = false;
	}

	SDL_Rect* GameController::checkPoint(SDL_Point* p) {
		for (auto& b : *gc.getBackgrounds()) {
			if (SDL_PointInRect(p, b->getRect())) {
				return b->getRect();
			}
		}
		return nullptr;
	}

	SDL_Rect* GameController::getMPos() {
		return checkPoint(p);
	}

	GameController::~GameController() {
		bgs.clear();
		collObjs.clear();
		SDL_DestroyRenderer(sys->getRen());
		SDL_DestroyWindow(sys->getWin());
		SDL_Quit();
	}

	GameController gc = *GameController::getInstance();

}