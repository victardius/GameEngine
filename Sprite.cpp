#include "Sprite.h"
#include "GameController.h"

namespace gameEngine {

	Sprite::Sprite(const char* path, int posX, int posY, int sizeW, int sizeH) {
		SDL_Surface* sf = IMG_Load(path);
		tx = SDL_CreateTextureFromSurface(gc.getRen(), sf);
		if (!(sizeW > 0 && sizeH > 0))
			SDL_QueryTexture(tx, NULL, NULL, &sizeW, &sizeH);
		rect = { posX, posY, sizeW, sizeH };
		SDL_FreeSurface(sf);
	}

	void Sprite::rdrCpy() {
		SDL_RenderCopy(gc.getRen(), tx, NULL, &rect);
	}

	void Sprite::moveTo(int newX, int newY) {
		rect.x = newX;
		rect.y = newY;
	}

	void Sprite::setSize(int sX, int sY) {
		rect.w = sX;
		rect.h = sY;
	}

	void Sprite::resetSize() {
		int sizeX, sizeY;
		SDL_QueryTexture(tx, NULL, NULL, &sizeX, &sizeY);
		rect.w = sizeX;
		rect.h = sizeY;
	}

	Sprite::~Sprite() {
		SDL_DestroyTexture(tx);
	}

}