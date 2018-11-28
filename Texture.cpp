#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

using namespace std;

Texture::Texture(const char* path, SDL_Renderer* rdr, int x, int y, int sizeX, int sizeY) {
	SDL_Surface* sf = IMG_Load(path);
	tx = SDL_CreateTextureFromSurface(rdr, sf);
	//tx = IMG_LoadTexture(rdr, path);
	SDL_QueryTexture(tx, NULL, NULL, &sizeX, &sizeY);
	rect = { x, y, sizeX, sizeY };
	SDL_FreeSurface(sf);
	cout << "Creating tx" << endl;
}

int Texture::getX() {
	return x;
} 

int Texture::getY() {
	return y;
}

void Texture::rdrCpy(SDL_Renderer* rdr) {
	SDL_RenderCopy(rdr, tx, NULL, &rect);
}

void Texture::moveTo(int x, int y) {
	rect.x = x;
	rect.y = y;
}

Texture::~Texture() {
	SDL_DestroyTexture(tx);
	cout << "Removing texture" << endl;
}