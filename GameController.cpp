#include "GameController.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#define FPS 60

void GameController::init() {
	SDL_Init(SDL_INIT_EVERYTHING);

	int flags = IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted&flags) != flags) {
		std::cout << "IMG_Init: Failed to init required png support!\n" << std::endl;
		std::cout << "IMG_Init: %s\n" << IMG_GetError() << std::endl;
	}

	win = SDL_CreateWindow("Game", 100, 100, 960, 540, 0);
	ren = SDL_CreateRenderer(win, -1, 0);

}

void GameController::eventHandler() {
	const int tickInterval = 1000 / FPS;
	bool running = true;
	while (running) {
		Uint32 nextTick = SDL_GetTicks() + tickInterval;
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT: running = false; break;
				
			}
		}
		renderReset();

		int delay = nextTick - SDL_GetTicks();
		if (delay > 0)
			SDL_Delay(delay);
	}
}

void GameController::renderReset() {
	SDL_RenderClear(ren);
	for (auto& t : textures) {
		t.second->rdrCpy(ren);
	}
	SDL_RenderPresent(ren);
}

void GameController::addTexture(const char* path, std::string name, int x, int y, int sizeX, int sizeY) {
	Texture* tx = new Texture(path, ren, x, y, sizeX, sizeY);
	textures.emplace(name, tx);
}

void GameController::end() {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}