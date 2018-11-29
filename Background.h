#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Sprite.h"

class Background : public Sprite::Sprite {
public:
	Background(const char* path, SDL_Renderer* rdr, int x = 0, int y = 0, int sizeX = 0, int sizeY = 0) : Sprite::Sprite(path, rdr, x, y, sizeX, sizeY) {}
private:
};

#endif
