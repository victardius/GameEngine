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
		static EventController* getInstance() {
			return new EventController();
		}
		void eventHandler();
		void SetRightMouseButton(void (*function)());
		void SetLeftMouseButton(void(*function)());
		void SetEscapeKey(void(*function)());
		void quit();
	protected:
		EventController();
		SDL_Rect* checkPoint(SDL_Point* p);
	private:
		void mouseDown(SDL_MouseButtonEvent* mb);
		void keyDown(SDL_Keycode* key);
		bool running;
		void(*rightMB)();
		void(*leftMB)();
		void(*keyEscape)();
	};

}

#endif

