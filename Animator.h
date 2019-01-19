#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <SDL.h>
#include <SDL_image.h>
#include <memory>

namespace gameEngine {

	class Animator
	{
	public:
		static std::shared_ptr<Animator> getInstance(const char* sheetPath, int w = 0, int h = 0, int frames = 1);
		const SDL_Rect* getRect();
		const SDL_Rect* getActiveRect(int frame);
		SDL_Surface* getSurf();
		SDL_Texture* getTx();
		int getFrames() const;
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