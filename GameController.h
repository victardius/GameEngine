#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <string>
#include <iostream>
#include "Sprite.h"
#include "Character.h"

namespace gameEngine {

	class GameController {
	public:
		GameController();
		//void eventHandler();
		void addBackground(const char* path, std::string name, int x = 0, int y = 0, int sizeX = 0, int sizeY = 0);
		Character* addCharacter(int pHealth, double pSpeed, const char* path, std::string name, int x = 0, int y = 0, int sizeX = 0, int sizeY = 0);
		~GameController();
		//void mouseClick(SDL_MouseButtonEvent* mb);
		void renderReset();
		void createBG(int amount, const char* path);
		SDL_Renderer* getRen();
		std::unordered_map<std::string, CollisionSprite*>* getCollidingObjects();
		std::unordered_map<std::string, Background*>* getBackgrounds();
		void removeCollidingObject(std::string n);
		void removeBackground(std::string n);
	private:
		std::unordered_map<std::string, CollisionSprite*> collObjs;
		std::unordered_map<std::string, Background*> bgs;
		//Character* player;
		SDL_Window* win;
		SDL_Renderer* ren;
		//SDL_Rect* checkPoint(SDL_Point* p);
	};

	extern GameController gc;

}

#endif
