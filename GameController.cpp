#include "GameController.h"
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
				case SDL_MOUSEBUTTONDOWN:{
					SDL_Point p = { event.button.x, event.button.y };
					mouseClick(event.button, p);
					} break;
			}
		}
		renderReset();

		int delay = nextTick - SDL_GetTicks();
		if (delay > 0)
			SDL_Delay(delay);
	}
}

void GameController::mouseClick(SDL_MouseButtonEvent mb, SDL_Point p) {
	if (mb.button == SDL_BUTTON_RIGHT && SDL_PointInRect(&p, (sprites.at("background")->getRect()))) {
		player->move(bg.at("background")->getRect(), this);
	}
}

void GameController::renderReset() {
	SDL_RenderClear(ren);
	for (auto& t : sprites) {
		t.second->rdrCpy(ren);
	}
	SDL_RenderPresent(ren);
}

void GameController::addBackground(const char* path, std::string name, int x, int y, int sizeX, int sizeY) {
	Background* tx = new Background(path, ren, x, y, sizeX, sizeY);
	sprites.emplace(name, tx);
	bg.emplace(name, tx);
}

void GameController::addPlayer(int pHealth, double pSpeed, const char* path, std::string name, int x, int y, int sizeX, int sizeY) {
	Character* tx = new Character(pHealth, pSpeed, path, ren, x, y, sizeX, sizeY);
	sprites.emplace(name, tx);
	player = tx;
}

void GameController::end() {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}