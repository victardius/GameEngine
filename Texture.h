#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SDL.h>

class Texture {
public:
	Texture(char* path, SDL_Renderer* rdr, int x = 0, int y = 0, int sizeX = 0, int sizeY = 0);
	int getX();
	int getY();
	void moveTo(int x, int y);
	void moveAmount(int x, int y);
	void setTexture(string path);
	void setSize(int sizeX, int sizeY);
	void resetSize();
private:
	int x, y, sizeX, sizeY;
	SDL_Rect rect;
}

#endif

