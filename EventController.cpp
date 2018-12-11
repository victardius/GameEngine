#include "EventController.h"
#include "GameController.h"

#define FPS 60

namespace gameEngine {

	EventController::EventController()
	{
		eventHandler();
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
	
	void EventController::mouseDown(SDL_MouseButtonEvent* mb) {
		SDL_Point p = { mb->x, mb->y };
		SDL_Rect* r = checkPoint(&p);
		if (mb->button == SDL_BUTTON_RIGHT) {
			if (r != nullptr)
				rightMB;
		}
		else if (mb->button == SDL_BUTTON_LEFT) {
			if (r != nullptr)
				leftMB;
		}
	}

	void EventController::keyDown(SDL_Keycode* key) {
		if (*key == SDLK_ESCAPE)
			keyEscape;
	}

	void EventController::SetRightMouseButton(void(*function)()) {
		rightMB = function;
	}

	void EventController::SetLeftMouseButton(void(*function)()) {
		leftMB = function;
	}

	void EventController::SetEscapeKey(void(*function)()) {
		keyEscape = function;
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

	EventController::~EventController()
	{
	}

}