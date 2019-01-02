#ifndef COLLIDER_H
#define COLLIDER_H
#include <SDL.h>

struct Collider
{
	Collider(SDL_Rect* r, int xx, int yy) : rect(r), x(xx), y(yy) {};
	SDL_Rect* rect;
	int x, y;
};

#endif