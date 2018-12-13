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
		static GameController* getInstance();
		void addBackground(const char* path, std::string name, int x = 0, int y = 0, int sizeX = 0, int sizeY = 0);
		Character* addCharacter(int pHealth, int pSpeed, const char* path, std::string name, int x = 0, int y = 0, int sizeX = 0, int sizeY = 0);
		~GameController();
		void renderReset();
		void createBG(int amount, const char* path);
		SDL_Renderer* getRen();
		std::vector<CollisionSprite*>* getCollidingObjects();
		std::vector<Background*>* getBackgrounds();
		void removeCollidingObject(CollisionSprite* n);
		void removeBackground(Background* n);
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
	protected:
		GameController();
	private:
		SDL_Rect* checkPoint(SDL_Point* p);
		std::vector<CollisionSprite*> collObjs;
		std::vector<Background*> bgs;
		std::vector<CollisionSprite*> removeCollObjs;
		std::vector<Background*> removeBgs;
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
		void removeObjects();
	};

	extern GameController gc;

}

#endif
