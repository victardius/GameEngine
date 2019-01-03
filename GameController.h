#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SDL.h>
#include <SDL_image.h>
#include <utility>
#include <memory>
#include "CollisionSprite.h"
#include "Background.h"
#include "System.h"
#include "Text.h"

namespace gameEngine {

	class GameController {
	public:
		static GameController* getInstance();
		void addBackground(std::shared_ptr<Background> bg);
		void addCollisionSprite(std::shared_ptr<CollisionSprite> character);
		void addText(std::shared_ptr<Text> text);
		~GameController();
		void renderReset();
		void createBG(int amount, std::shared_ptr<Animator> animat);
		std::vector<std::shared_ptr<CollisionSprite>>* getCollidingObjects();
		std::vector<std::shared_ptr<Background>>* getBackgrounds();
		std::vector<std::shared_ptr<Text>>* getTexts();
		void removeCollidingObject(std::shared_ptr<CollisionSprite> n);
		void removeBackground(std::shared_ptr<Background> n);
		void removeText(std::shared_ptr<Text> n);
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
		std::vector<std::shared_ptr<CollisionSprite>> collObjs;
		std::vector<std::shared_ptr<Background>> bgs;
		std::vector<std::shared_ptr<Text>> texts;
		std::vector<std::shared_ptr<CollisionSprite>> removeCollObjs;
		std::vector<std::shared_ptr<Background>> removeBgs;
		std::vector<std::shared_ptr<Text>> removeTexts;
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
