#include "GameController.h"

namespace gameEngine {

	GameController::GameController() {
		sys = System::getInstance();
		SDL_StartTextInput();
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
		for (auto& co1 : *level->getCollidingObjects()) {
			for (auto& co2 : *level->getCollidingObjects()) {
				if (co1 != co2) {
					co1->checkCollision(co2);
				}
			}
		}
		SDL_RenderClear(sys->getRen());
		for (auto& bg : *level->getBackgrounds()) {
			bg->tick();
		}
		for (auto& co : *level->getCollidingObjects()) {
			co->tick();
		}
		for (auto& txt : *level->getTexts()) {
			if (txt->isActive())
				txt->setText(text);
			txt->tick();
		}
		SDL_RenderPresent(sys->getRen());
	}

	void GameController::eventHandler() {
		const int tickInterval = 1000 / fps;
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
				case SDL_TEXTINPUT: {
					if (typing)
						text += event.text.text;
				} break;
				}
			}
			level->removeObjects();
			renderReset();
			int delay = nextTick - SDL_GetTicks();
			if (delay > 0)
				SDL_Delay(delay);
		}
	}
	
	void GameController::mouseDown(SDL_MouseButtonEvent* mb) {
		SDL_Point point = { mb->x, mb->y };
		p = &point;
		startFunctions(mb->button);
	}

	void GameController::keyDown(SDL_Keycode key) {
		startFunctions(key);
		editText(key);
	}

	void GameController::startFunctions(const int key) {
		if (functions.count(key))
			functions[key]();
	}

	void GameController::editText(SDL_Keycode event) {
		if (event == SDLK_BACKSPACE && text.length() > 0) {
			text.pop_back();
		}
	}

	void GameController::quit() {
		running = false;
	}

	void GameController::addFunction(int i, std::function<void()> f) {
		functions[i] = f;
	}

	SDL_Rect* GameController::checkPoint(SDL_Point* p) {
		for (auto& b : *level->getBackgrounds()) {
			if (SDL_PointInRect(p, b->getRect())) {
				return b->getRect();
			}
		}
		return nullptr;
	}

	SDL_Rect* GameController::getMPos() {
		return checkPoint(p);
	}

	void GameController::setFPS(int f) {
		if (f > 0)
			fps = f;
		else
			std::cerr << "Invalid input, FPS must be a number above zero" << std::endl;
	}

	int GameController::getFPS() {
		return fps;
	}

	void GameController::setTyping(bool b) {
		typing = b;
	}

	void GameController::setLevel(std::shared_ptr<Level> l) {
		level = l;
	}

	std::shared_ptr<Level> GameController::getLevel() {
		return level;
	}

	GameController::~GameController() {
		SDL_Quit();
	}

	GameController gc = *GameController::getInstance();

}