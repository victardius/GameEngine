#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <SDL.h>
#include <SDL_image.h>

namespace gameEngine {

	class Animator
	{
	public:
		static Animator* getInstance(const char* sheetPath, int w, int h, int frames);
		void renderFrame(int frame, SDL_Rect* dest);
		void setAngleBased(bool b);
		bool isAngleBased();
		~Animator();
	protected:
		Animator(const char* sheetPath, int w, int h, int frames);
	private:
		SDL_Surface* sf;
		SDL_Texture* tx;
		SDL_Rect* rect;
		bool angleBased = false;
		int totSizeW, totSizeH, frames;
	};

}

#endif