#include "GameController.h"

#define FPS 60

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

	GameController* GameController::getInstance() {
		return new GameController();
	}

	void GameController::start() {
		for (auto& co : collObjs) {
			co->createColliders();
		}
		eventHandler();
	}

	void GameController::renderReset() {
		renderStart = SDL_GetTicks();
		for (auto& co1 : collObjs) {
			for (auto& co2 : collObjs) {
				if (co1 != co2) {
					co1->checkCollision(co2);
				}
			}
		}
		SDL_RenderClear(ren);
		for (auto& bg : bgs) {
			bg->tick();
		}
		for (auto& co : collObjs) {
			co->tick();
		}
		SDL_RenderPresent(ren);
	}

	int GameController::getRenderStart() {
		return renderStart;
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

	SDL_Renderer* GameController::getRen() {
		return ren;
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
		if (mb->button == SDL_BUTTON_RIGHT) {
			rightMB();
		}
		else if (mb->button == SDL_BUTTON_LEFT) {
			leftMB();
		}
	}

	void GameController::keyDown(SDL_Keycode* key) {
		if (*key == SDLK_ESCAPE)
			keyEscape();
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
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
	}

	GameController gc = *GameController::getInstance();

}