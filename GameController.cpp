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
		eventHandler();
	}

	void GameController::renderReset() {
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
		for (auto& txt : texts) {
			txt->tick();
		}
		SDL_RenderPresent(sys->getRen());
	}

	void GameController::addBackground(std::shared_ptr<Background> bg) {
		bgs.push_back(bg);
	}

	void GameController::addCollisionSprite(std::shared_ptr<CollisionSprite> character) {
		collObjs.push_back(character);
	}

	void GameController::addText(std::shared_ptr<Text> text) {
		texts.push_back(text);
	}

	void GameController::createBG(int amount, std::shared_ptr<Animator> animat) {
		std::string name = "background0";
		char c = '0';
		int posX = 0, posY = 0, total = 0;
		for (int i = 0; i < amount; i++) {
			name.replace(10, 1, &c);
			c++;
			addBackground(Background::getInstance(animat, name, posX, posY));
			posX += 64;
			if (posX == 640) {
				posX = 0;
				posY += 64;
			}
		}
	}

	std::vector<std::shared_ptr<CollisionSprite>>* GameController::getCollidingObjects() {
		return &collObjs;
	}

	std::vector<std::shared_ptr<Background>>* GameController::getBackgrounds() {
		return &bgs;
	}

	std::vector<std::shared_ptr<Text>>* GameController::getTexts() {
		return &texts;
	}

	void GameController::removeCollidingObject(std::shared_ptr<CollisionSprite> n) {
		removeCollObjs.push_back(n);
	}

	void GameController::removeBackground(std::shared_ptr<Background> n) {
		removeBgs.push_back(n);
	}

	void GameController::removeText(std::shared_ptr<Text> n) {
		removeTexts.push_back(n);
	}

	void GameController::removeObjects() {
		for (std::shared_ptr<CollisionSprite> cs : removeCollObjs) {
			for (std::vector<std::shared_ptr<CollisionSprite>>::iterator i = collObjs.begin(); i != collObjs.end(); )
				if (*i == cs) {
					i = collObjs.erase(i);
				}
				else
					i++;
		}
		removeCollObjs.clear();

		for (std::shared_ptr<Background> bg : removeBgs) {
			for (std::vector<std::shared_ptr<Background>>::iterator i = bgs.begin(); i != bgs.end(); )
				if (*i == bg) {
					i = bgs.erase(i);
				}
				else
					i++;
		}
		removeBgs.clear();

		for (std::shared_ptr<Text> txt : removeTexts) {
			for (std::vector<std::shared_ptr<Text>>::iterator i = texts.begin(); i != texts.end(); )
				if (*i == txt) {
					i = texts.erase(i);
				}
				else
					i++;
		}
		removeTexts.clear();
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
					keyDown(event.key.keysym.sym);
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
		keyDown(mb->button);
	}

	void GameController::keyDown(const int key) {
		for (auto& func : functions)
			if (func.first == key)
				func.second();
	}

	void GameController::quit() {
		running = false;
	}

	void GameController::addFunction(int i, void(*f)()) {
		functions.push_back(std::make_pair(i, f));
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
		SDL_Quit();
	}

	GameController gc = *GameController::getInstance();

}