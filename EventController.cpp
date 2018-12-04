#include "EventController.h"
#include "GameController.h"

#define FPS 60

using namespace gameEngine;

EventController::EventController()
{
	
}

EventController* EventController::getInstance() {
	return new EventController();
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
					mouseClick(&event.button);
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

void EventController::mouseClick(SDL_MouseButtonEvent* mb) {
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

void EventController::keyDown(SDL_Keycode* key) {
	if (*key == SDLK_ESCAPE)
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

void EventController::addPlayer(int pHealth, double pSpeed, const char* path, std::string name, int x, int y, int sizeX, int sizeY) {
	player = gc.addCharacter(pHealth, pSpeed, path, name, x, y, sizeX, sizeY);
}

EventController::~EventController()
{
}
