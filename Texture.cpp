#include "Texture.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;


Texture::Texture(char* path, SDL_Renderer* rdr, int x = 0, int y = 0, int sizeX = 0, int sizeY = 0) {
	SDL_Surface* sf = IMG_Load(path);
	SDL_Texture* tx = SDL_CreateTextureFromSurface(rdr, sf);
	if (sizeX + sizeY == 0)
		SDL_QueryTexture(tx, NULL, NULL, &sizeX, &sizeY);
	rect = { x, y, sizeX, sizeY };
	SDL_FreeSurface(sf);
	SDL_RenderCopy(rdr, tx, NULL, &rect);
}

int Texture::getX() {
	return x;
}

int Texture::getY() {
	return y;
}

void Texture::moveTo(int x, int y) {
	rect.x = x;
	rect.y = y;
}