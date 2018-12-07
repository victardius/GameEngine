#include "EventController.h"
#include "GameController.h"

#define FPS 60

namespace gameEngine {

	EventController::EventController()
	{
		
	}

	void EventController::eventHandler() {
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
			gc.renderReset();
			int delay = nextTick - SDL_GetTicks();
			if (delay > 0)
				SDL_Delay(delay);
		}
	}

	void EventController::quit() {
		running = false;
	}

	SDL_Rect* EventController::checkPoint(SDL_Point* p) {
		for (auto& b : *gc.getBackgrounds()) {
			if (SDL_PointInRect(p, b.second->getRect())) {
				return b.second->getRect();
			}
		}
		return nullptr;
	}

	void EventController::addPlayer(int pHealth, int pSpeed, const char* path, std::string name, int x, int y, int sizeX, int sizeY) {
		player = gc.addCharacter(pHealth, pSpeed, path, name, x, y, sizeX, sizeY);
	}

	Character* EventController::getPlayer() {
		return player;
	}

	EventController::~EventController()
	{
	}

}