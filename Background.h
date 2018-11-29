#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Sprite.h"

class Background : public Sprite {
public:
	Background(const char* path, SDL_Renderer* rdr, int x, int y, int sizeX, int sizeY) : Sprite(path, rdr, x, y, sizeX, sizeY) {}
private:
};

#endif
