#include "Sprite.h"
#include "GameController.h"

namespace gameEngine {

	Sprite::Sprite(Animator* animat, std::string spriteName, int posX, int posY) : name(spriteName), startX(posX), startY(posY), anim(animat){
		setTexture(posX, posY);
	}

	void Sprite::setTexture(int posX, int posY) {
		rect = new SDL_Rect { posX, posY, anim->getRect()->w, anim->getRect()->h };
	}

	void Sprite::tick() {
		tickFunction();
		rdrCpy();
	}

	void Sprite::rdrCpy() {
		SDL_RenderCopy(gc.getSys()->getRen(), anim->getTx(), anim->getActiveRect(currentFrame), rect);
	}

	void Sprite::moveTo(int newX, int newY) {
		rect->x = newX;
		rect->y = newY;
	}

	std::string Sprite::getName() {
		return name;
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

	int Sprite::getXSinceStart() {
		return startX - getRect()->x;
	}

	int Sprite::getYSinceStart() {
		return startY - getRect()->y;
	}

	void Sprite::changeFrame(int f) {
		currentFrame = f;
	}

	int Sprite::getCurrentFrame() {
		return currentFrame;
	}

	Sprite::~Sprite() {
	}

}