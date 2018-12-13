#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

namespace gameEngine {

	class System
	{
	public:
		static System* getInstance();
		~System();
		//int getRenderStart();
		SDL_Renderer* getRen();
		SDL_Window* getWin();
	private:
		System();
		SDL_Window* win;
		SDL_Renderer* ren;
		//int renderStart;
	};

}

#endif