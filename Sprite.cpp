#include "Sprite.h"

Sprite::Sprite(const char* path, SDL_Renderer* rdr, int posX, int posY, int sizeW, int sizeH) {
	SDL_Surface* sf = IMG_Load(path);
	tx = SDL_CreateTextureFromSurface(rdr, sf);
	if (!(sizeW > 0 && sizeH > 0))
		SDL_QueryTexture(tx, NULL, NULL, &sizeW, &sizeH);
	rect = { posX, posY, sizeW, sizeH };
	SDL_FreeSurface(sf);
	std::cout << "Creating tx with size: " << rect.w << " x " << rect.h << std::endl;
	std::cout << "Creating tx with pos: " << rect.x << " x " << rect.y << std::endl;
}

void Sprite::rdrCpy(SDL_Renderer* rdr) {
	SDL_RenderCopy(rdr, tx, NULL, &rect);
}

void Sprite::moveTo(int newX, int newY) {
	rect.x = newX;
	rect.y = newY;
}

void Sprite::setSize(int sX, int sY) {
	rect.w = sX;
	rect.h = sY;
}

void Sprite::resetSize() {
	int sizeX, sizeY;
	SDL_QueryTexture(tx, NULL, NULL, &sizeX, &sizeY);
	rect.w = sizeX;
	rect.h = sizeY;
}

Sprite::~Sprite() {
	SDL_DestroyTexture(tx);
	std::cout << "Removing texture" << std::endl;
}