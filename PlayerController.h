#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "EventController.h"

using namespace gameEngine;

class PlayerController: public EventController
{
public:
	PlayerController();
	~PlayerController();
protected:
	
private:
	virtual void mouseDown(SDL_MouseButtonEvent* mb);
	virtual void keyDown(SDL_Keycode* key);
};

extern PlayerController pc;

#endif

