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
		SDL_Texture* getTx();
		SDL_Rect* getRect();
		SDL_Rect* getActiveRect();
		void moveTo(int x, int y);
		void setTexture(const char* path, int posX, int posY, int sizeW, int sizeH);
		void setSize(int sizeX, int sizeY);
		virtual void tick(); //måste returnera nåt senare
		SDL_Surface* getSurface();
		std::string getName();
		virtual void setAnimation(Animator* anim);
		Animator* getAnimation();
		int getXSinceStart();
		int getYSinceStart();
		~Sprite();
	protected:
		Sprite(const char* path, std::string spriteName, int posX = 0, int posY = 0, int sizeW = 0, int sizeH = 0);
		virtual void rdrCpy();
	private:
		SDL_Texture* tx;
		SDL_Rect* rect;
		SDL_Rect* activeRect;
		SDL_Surface* sf;
		std::string name;
		Animator* anim = nullptr;
		int startX, startY;
	};

}

#endif

