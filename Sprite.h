#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <iostream>

class Sprite {
public:
	Sprite(const char* path, SDL_Renderer* rdr, int x = 0, int y = 0, int sizeX = 0, int sizeY = 0);
	int getX();
	int getY();
	SDL_Texture* getTx() { return tx; };
	SDL_Rect getRect() { return rect; };
	void rdrCpy(SDL_Renderer* rdr);
	void moveTo(int x, int y);
	void setTexture(char* path, SDL_Renderer* rdr) { Sprite::Sprite(path, rdr); };
	void setSize(int sizeX, int sizeY);
	void resetSize();
	~Sprite();
private:
	int x, y, sizeX, sizeY;
	SDL_Texture* tx;
	SDL_Rect rect;
};

#endif

