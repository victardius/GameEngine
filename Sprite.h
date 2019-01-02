#ifndef SPRITE_H
#define SPRITE_H

#include "Animator.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

namespace gameEngine {

	class Sprite {
	public:
		SDL_Rect* getRect();
		void moveTo(int x, int y);
		virtual void tick();
		std::string getName();
		virtual void setAnimation(Animator* anim);
		Animator* getAnimation();
		int getXSinceStart();
		int getYSinceStart();
		void changeFrame(int f);
		int getCurrentFrame();
		~Sprite();
	protected:
		Sprite(Animator* animat, std::string spriteName, int posX = 0, int posY = 0);
		void rdrCpy();
		virtual void tickFunction() = 0;
	private:
		SDL_Rect* rect;
		std::string name;
		Animator* anim = nullptr;
		int startX, startY, currentFrame = 0;
		void setTexture(int posX, int posY);
	};

}

#endif

