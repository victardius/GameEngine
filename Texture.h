#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

class Texture {
public:
	Texture(const char* path, SDL_Renderer* rdr, int x = 0, int y = 0, int sizeX = 0, int sizeY = 0);
	int getX();
	int getY();
	SDL_Texture* getTx() { return tx; };
	SDL_Rect getRect() { return rect; };
	void rdrCpy(SDL_Renderer* rdr);
	void moveTo(int x, int y);
	void moveAmount(int x, int y);
	void setTexture(char* path);
	void setSize(int sizeX, int sizeY);
	void resetSize();
	~Texture();
private:
	int x, y, sizeX, sizeY;
	SDL_Texture* tx;
	SDL_Rect rect;
};

#endif

