#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SDL.h>
#include <SDL_image.h>
#include <utility>
#include "CollisionSprite.h"
#include "Background.h"
#include "System.h"

namespace gameEngine {

	class GameController {
	public:
		static GameController* getInstance();
		void addBackground(Background* bg);
		CollisionSprite* addCollisionSprite(CollisionSprite* character);
		~GameController();
		void renderReset();
		void createBG(int amount, Animator* animat);
		std::vector<CollisionSprite*>* getCollidingObjects();
		std::vector<Background*>* getBackgrounds();
		void removeCollidingObject(CollisionSprite* n);
		void removeBackground(Background* n);
		void start(); 
		void eventHandler();
		void quit();
		void addFunction(int i, void(*f)());
		SDL_Rect* getMPos();
		System* getSys();
	protected:
		GameController();
	private:
		SDL_Rect* checkPoint(SDL_Point* p);
		std::vector<CollisionSprite*> collObjs;
		std::vector<Background*> bgs;
		std::vector<CollisionSprite*> removeCollObjs;
		std::vector<Background*> removeBgs;
		std::vector<std::pair<int, void(*)()>> functions;
		void mouseDown(SDL_MouseButtonEvent* mb);
		void keyDown(const int key);
		bool running;
		SDL_Point* p;
		void removeObjects();
		System* sys;
	};

	extern GameController gc;

}

#endif
