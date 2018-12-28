#include "System.h"

namespace gameEngine {

	System::System()
	{
		SDL_Init(SDL_INIT_EVERYTHING);

		int flags = IMG_INIT_PNG;
		int initted = IMG_Init(flags);
		if ((initted&flags) != flags) {
			std::cout << "IMG_Init: Failed to init required png support!\n" << std::endl;
			std::cout << "IMG_Init: %s\n" << IMG_GetError() << std::endl;
		}

		win = SDL_CreateWindow("Game", 100, 100, 640, 640, 0);
		ren = SDL_CreateRenderer(win, -1, 0);
	}

	System* System::getInstance() {
		return new System();
	}

	/*int System::getRenderStart() {
		return renderStart;
	}*/

	SDL_Renderer* System::getRen() {
		return ren;
	}

	SDL_Window* System::getWin() {
		return win;
	}

	System::~System()
	{
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
	}

}