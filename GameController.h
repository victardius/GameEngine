#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <string>
#include <iostream>
#include "Sprite.h"
#include "Character.h"
#define FPS 60

namespace gameEngine {

	class GameController {
	public:
		GameController();
		void eventHandler();
		void addBackground(const char* path, std::string name, int x = 0, int y = 0, int sizeX = 0, int sizeY = 0);
		void addPlayer(int pHealth, double pSpeed, const char* path, std::string name, int x = 0, int y = 0, int sizeX = 0, int sizeY = 0);
		~GameController();
		void mouseClick(SDL_MouseButtonEvent* mb);
		void renderReset();
		void renderCharacters(int x, int y);
		void createBG(int amount, const char* path);
		SDL_Renderer* getRen();
	private:
		std::unordered_map<std::string, Sprite*> chars;
		std::unordered_map<std::string, Background*> bg;
		Character* player;
		SDL_Window* win;
		SDL_Renderer* ren;
		SDL_Rect* checkPoint(SDL_Point* p);
		Uint32 nextTick;
		const int tickInterval = 1000 / FPS;
	};

	extern GameController gc;

}

#endif
