#include "Sprite.h"
#include "GameController.h"

namespace gameEngine {

	Sprite::Sprite(std::shared_ptr<Animator> animat, std::string spriteName, int posX, int posY) : name(spriteName), anim(animat){
		setTexture(posX, posY);
	}

	void Sprite::setTexture(int posX, int posY) {
		if (anim != NULL || anim != nullptr)
			rect = new SDL_Rect { posX, posY, anim->getRect()->w, anim->getRect()->h };
		else
			rect = new SDL_Rect{ posX, posY, 0, 0 };
	}

	void Sprite::tick() {
		tickFunction();
		rdrCpy();
	}

	void Sprite::rdrCpy() {
		if (anim != NULL || anim != nullptr)
			SDL_RenderCopy(gc.getSys()->getRen(), anim->getTx(), anim->getActiveRect(currentFrame), rect);
	}

	std::string Sprite::getName() {
		return name;
	}

	SDL_Rect* Sprite::getRect() {
		return rect;
	}

	void Sprite::setAnimation(std::shared_ptr<Animator> ani) {
		anim = std::shared_ptr<Animator>(ani);
	}

	std::shared_ptr<Animator> Sprite::getAnimation() {
		return anim;
	}

	void Sprite::changeFrame(int f) {
		currentFrame = f;
	}

	int Sprite::getCurrentFrame() {
		return currentFrame;
	}

	void Sprite::changeSize(double n) {
		rect->h = (int)(rect->h * n);
		rect->w = (int)(rect->h * n);
	}

	Sprite::~Sprite() {
		anim.reset();
	}

}