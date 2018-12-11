#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <string>
#include <iostream>
#include "Sprite.h"
#include "Character.h"
#include "EventController.h"

namespace gameEngine {

	class GameController {
	public:
		GameController();
		void addBackground(const char* path, std::string name, int x = 0, int y = 0, int sizeX = 0, int sizeY = 0);
		Character* addCharacter(int pHealth, int pSpeed, const char* path, std::string name, int x = 0, int y = 0, int sizeX = 0, int sizeY = 0);
		~GameController();
		void renderReset();
		void createBG(int amount, const char* path);
		SDL_Renderer* getRen();
		std::unordered_map<std::string, CollisionSprite*>* getCollidingObjects();
		std::unordered_map<std::string, Background*>* getBackgrounds();
		void removeCollidingObject(std::string n);
		void removeBackground(std::string n);
		int getRenderStart();
		Character* getPlayer();
		void setPlayer(Character* p);
		void start(); 
		void eventHandler();
		void SetRightMouseButton(void(*function)());
		void SetLeftMouseButton(void(*function)());
		void SetEscapeKey(void(*function)());
		void quit();
		SDL_Rect* getMPos();
	private:
		SDL_Rect* checkPoint(SDL_Point* p);
		std::unordered_map<std::string, CollisionSprite*> collObjs;
		std::unordered_map<std::string, Background*> bgs;
		SDL_Window* win;
		SDL_Renderer* ren;
		Character* player;
		int renderStart;
		void mouseDown(SDL_MouseButtonEvent* mb);
		void keyDown(SDL_Keycode* key);
		bool running;
		void(*rightMB)();
		void(*leftMB)();
		void(*keyEscape)();
		SDL_Point* p;
	};

	extern GameController gc;

}

#endif
