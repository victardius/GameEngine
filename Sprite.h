#ifndef SPRITE_H
#define SPRITE_H

#include "Animator.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <memory>

namespace gameEngine {

	class Sprite {
	public:
		SDL_Rect* getRect();
		virtual void tick();
		std::string getName();
		virtual void setAnimation(std::shared_ptr<Animator> anim);
		std::shared_ptr<Animator> getAnimation();
		void changeFrame(int f);
		int getCurrentFrame();
		void changeSize(double n);
		~Sprite();
	protected:
		Sprite(std::shared_ptr<Animator> animat, std::string spriteName, int posX = 0, int posY = 0);
		void rdrCpy();
		virtual void tickFunction() = 0;
	private:
		SDL_Rect* rect;
		std::string name;
		std::shared_ptr<Animator> anim = nullptr;
		int currentFrame = 0;
		void setTexture(int posX, int posY);
	};

}

#endif

