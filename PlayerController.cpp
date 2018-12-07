#include "PlayerController.h"



PlayerController::PlayerController(): EventController()
{
}

void PlayerController::mouseDown(SDL_MouseButtonEvent* mb) {
	SDL_Point p = { mb->x, mb->y };
	SDL_Rect* r = checkPoint(&p);
	if (mb->button == SDL_BUTTON_RIGHT) {
		if (r != nullptr)
			getPlayer()->moveTarget(r);
	}
	else if (mb->button == SDL_BUTTON_LEFT) {
		if (r != nullptr)
			getPlayer()->shoot(r);
	}
}

void PlayerController::keyDown(SDL_Keycode* key) {
	if (*key == SDLK_ESCAPE)
		quit();
}


PlayerController::~PlayerController()
{
}

PlayerController pc;
