#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

namespace gameEngine {

	class System
	{
	public:
		static System* getInstance();
		~System();
		SDL_Renderer* getRen();
		const SDL_Window* getWin();
	private:
		System();
		SDL_Window* win;
		SDL_Renderer* ren;
	};

}

#endif