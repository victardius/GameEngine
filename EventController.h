#ifndef EVENTCONTROLLER_H
#define EVENTCONTROLLER_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Sprite.h"
#include "Character.h"

using namespace gameEngine;

class EventController
{
public:
	~EventController();
	static EventController* getInstance();
	void eventHandler();
	void addPlayer(int pHealth, double pSpeed, const char* path, std::string name, int x = 0, int y = 0, int sizeX = 0, int sizeY = 0);
protected:
	EventController();
private:
	void mouseClick(SDL_MouseButtonEvent* mb);
	void keyDown(SDL_Keycode* key);
	SDL_Rect* checkPoint(SDL_Point* p);
	Character* player;
	bool running;
};

#endif

