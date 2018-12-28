#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <SDL.h>
#include <SDL_image.h>

namespace gameEngine {

	class Animator
	{
	public:
		static Animator* getInstance(const char* sheetPath, int w, int h, int frames);
		SDL_Rect* getRect();
		SDL_Rect* getActiveRect(int frame);
		SDL_Surface* getSurf();
		SDL_Texture* getTx();
		int getXDiff();
		int getYDiff();
		int getFrames();
		~Animator();
	protected:
		Animator(const char* sheetPath, int w, int h, int frames);
	private:
		SDL_Surface* sf;
		SDL_Texture* tx;
		SDL_Rect* rect;
		int totSizeW, totSizeH, frames;
	};

}

#endif