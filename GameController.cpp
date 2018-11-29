#include "GameController.h"
#define FPS 60

GameController::GameController() {
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
					mouseClick(&event.button, &p);
					} break;
			}
		}
		renderReset();

		int delay = nextTick - SDL_GetTicks();
		if (delay > 0)
			SDL_Delay(delay);
	}
}

void GameController::mouseClick(SDL_MouseButtonEvent* mb, SDL_Point* p) {
	if (mb->button == SDL_BUTTON_RIGHT) {
		while (player->move(checkPoint(p)) != 0) {
			renderReset();
		}
	}
}

SDL_Rect* GameController::checkPoint(SDL_Point* p) {
	for (auto& b : bg){
		if (SDL_PointInRect(p, b.second->getRect())) {
			return b.second->getRect();
		}
	}
	return NULL;
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

void GameController::createBG(int amount, const char* path) {
	std::string name = "background0";
	char c = '0';
	int posX = 0, posY = 0, total = 0;
	for (int i = 0; i < amount; i++) {
		name.replace(10, 1, &c);
		c++;
		this->addBackground(path, name, posX, posY);
		posX += 64;
		if (posX == 640) {
			posX = 0;
			posY += 64;
		}
		std::cout << posX << " : " << posY << std::endl;
	}
}

GameController::~GameController() {
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}