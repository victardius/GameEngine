#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>

namespace gameEngine {

	class Sprite {
	public:
		SDL_Texture* getTx() { return tx; };
		SDL_Rect* getRect() { return &rect; };
		virtual void rdrCpy();
		void moveTo(int x, int y);
		void setTexture(char* path) { Sprite::Sprite(path); };
		void setSize(int sizeX, int sizeY);
		void resetSize();
		~Sprite();
	protected:
		Sprite(const char* path, int posX = 0, int posY = 0, int sizeW = 0, int sizeH = 0);
	private:
		SDL_Texture* tx;
		SDL_Rect rect;
	};

}

#endif

