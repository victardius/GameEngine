#ifndef EVENTCONTROLLER_H
#define EVENTCONTROLLER_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Sprite.h"
#include "Character.h"

namespace gameEngine {

	class EventController
	{
	public:
		~EventController();
		void eventHandler();
		void addPlayer(int pHealth, int pSpeed, const char* path, std::string name, int x = 0, int y = 0, int sizeX = 0, int sizeY = 0);
		Character* getPlayer();
		void quit();
	protected:
		EventController();
		SDL_Rect* checkPoint(SDL_Point* p);
	private:
		virtual void mouseDown(SDL_MouseButtonEvent* mb) = 0;
		virtual void keyDown(SDL_Keycode* key) = 0;
		Character* player;
		bool running;
	};

}

#endif

