#include "Sprite.h"
#include "GameController.h"

namespace gameEngine {

	Sprite::Sprite(const char* path, std::string spriteName, int posX, int posY, int sizeW, int sizeH) {
		name = spriteName;
		setTexture(path, posX, posY, sizeW, sizeH);
	}

	void Sprite::setTexture(const char* path, int posX, int posY, int sizeW, int sizeH) {
		sf = IMG_Load(path);
		tx = SDL_CreateTextureFromSurface(gc.getSys()->getRen(), sf);
		if (!(sizeW > 0 && sizeH > 0))
			SDL_QueryTexture(tx, NULL, NULL, &sizeW, &sizeH);
		rect = new SDL_Rect { posX, posY, sizeW, sizeH };
		
	}

	void Sprite::tick() {
		rdrCpy();
	}

	void Sprite::rdrCpy() {
		SDL_RenderCopy(gc.getSys()->getRen(), tx, NULL, rect);
	}

	void Sprite::moveTo(int newX, int newY) {
		rect->x = newX;
		rect->y = newY;
	}

	void Sprite::setSize(int sX, int sY) {
		rect->w = sX;
		rect->h = sY;
	}

	std::string Sprite::getName() {
		return name;
	}

	SDL_Surface* Sprite::getSurface() {
		return sf;
	}

	SDL_Texture* Sprite::getTx() {
		return tx;
	}

	SDL_Rect* Sprite::getRect() {
		return rect;
	}

	void Sprite::setAnimation(Animator* ani) {
		anim = ani;
	}

	Animator* Sprite::getAnimation() {
		return anim;
	}

	Sprite::~Sprite() {
		SDL_FreeSurface(sf);
		SDL_DestroyTexture(tx);
	}

}