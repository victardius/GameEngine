#include "System.h"

namespace gameEngine {

	System::System()
	{
		SDL_Init(SDL_INIT_EVERYTHING);

		int imgFlags = IMG_INIT_PNG;
		int imgInitted = IMG_Init(imgFlags);
		if ((imgInitted&imgFlags) != imgFlags) {
			std::cerr << "IMG_Init: Failed to init required png support!\n" << std::endl;
			std::cerr << "IMG_Init: %s\n" << IMG_GetError() << std::endl;
		}

		if (TTF_Init() == -1) {
			printf("TTF_Init: %s\n", TTF_GetError());
			exit(2);
		}

		int mixFlags = MIX_INIT_OGG | MIX_INIT_MOD;
		int mixInitted = Mix_Init(mixFlags);
		if (mixInitted&mixFlags != mixFlags) {
			std::cerr << "Mix_Init: Failed to init required ogg and mod support!\n" << std::endl;
			std::cerr << "Mix_Init: %s\n" << Mix_GetError() << std::endl;
		}

		win = SDL_CreateWindow("Game", 100, 100, 640, 640, 0);
		ren = SDL_CreateRenderer(win, -1, 0);
	}

	System* System::getInstance() {
		return new System();
	}

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