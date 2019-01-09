#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SDL.h>
#include <SDL_image.h>
#include <utility>
#include <memory>
#include <unordered_map>
#include <functional>
#include "CollisionSprite.h"
#include "Background.h"
#include "System.h"
#include "Text.h"
#include "Level.h"

namespace gameEngine {

	class GameController {
	public:
		static GameController* getInstance();
		~GameController();
		void renderReset();
		void start(); 
		void eventHandler();
		void quit();
		void addFunction(int i, std::function<void()> f);
		SDL_Rect* getMPos();
		System* getSys();
		void setFPS(int f);
		int getFPS();
		void setTyping(bool b);
		void setLevel(std::shared_ptr<Level> l);
		std::shared_ptr<Level> getLevel();
	protected:
		GameController();
	private:
		std::shared_ptr<Level> level;
		SDL_Rect* checkPoint(SDL_Point* p);
		std::unordered_map<int, std::function<void()>> functions;
		void mouseDown(SDL_MouseButtonEvent* mb);
		void keyDown(SDL_Keycode key);
		void startFunctions(const int key);
		void editText(SDL_Keycode event);
		bool running;
		SDL_Point* p;
		System* sys;
		int fps = 60;
		std::string text;
		bool typing = false;
	};

	extern GameController gc;

}

#endif
