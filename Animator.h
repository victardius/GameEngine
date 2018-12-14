#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <SDL.h>
#include <SDL_image.h>

namespace gameEngine {

	class Animator
	{
	public:
		Animator* getInstance(const char* sheetPath, int w, int h, int frames);
		~Animator();
	protected:
		Animator(const char* sheetPath, int w, int h, int frames);
	private:
		SDL_Surface* sf;
		SDL_Texture* tx;
		SDL_Rect* rect;
		int totSizeW, totSizeH;
	};

}

#endif