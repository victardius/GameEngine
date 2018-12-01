#include "Background.h"

namespace gameEngine {

	Background::Background(const char* path, int x, int y, int sizeX, int sizeY) : Sprite(path, x, y, sizeX, sizeY) {

	}

	Background* Background::getInstance(const char* path, int x, int y, int sizeX, int sizeY) {
		return new Background(path, x, y, sizeX, sizeY);
	}

}