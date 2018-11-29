#include "Sprite.h"

Sprite::Sprite(const char* path, SDL_Renderer* rdr, int x, int y, int sizeX, int sizeY) {
	SDL_Surface* sf = IMG_Load(path);
	tx = SDL_CreateTextureFromSurface(rdr, sf);
	if (!(sizeX > 0 && sizeY > 0))
		SDL_QueryTexture(tx, NULL, NULL, &sizeX, &sizeY);
	rect = { x, y, sizeX, sizeY };
	SDL_FreeSurface(sf);
	std::cout << "Creating tx" << std::endl;
}

int Sprite::getX() {
	return x;
} 

int Sprite::getY() {
	return y;
}

void Sprite::rdrCpy(SDL_Renderer* rdr) {
	SDL_RenderCopy(rdr, tx, NULL, &rect);
}

void Sprite::moveTo(int newX, int newY) {
	x = newX;
	y = newY;
	rect.x = newX;
	rect.y = newY;
}

void Sprite::setSize(int sX, int sY) {
	sizeX = sX;
	sizeY = sY;
	rect.w = sX;
	rect.h = sY;
}

void Sprite::resetSize() {
	SDL_QueryTexture(tx, NULL, NULL, &sizeX, &sizeY);
	rect.w = sizeX;
	rect.h = sizeY;
}

Sprite::~Sprite() {
	SDL_DestroyTexture(tx);
	std::cout << "Removing texture" << std::endl;
}