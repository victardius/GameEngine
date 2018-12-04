#include "Background.h"
#include "GameController.h"

namespace gameEngine {

	Background::Background(const char* path, std::string spriteName, int x, int y, int sizeX, int sizeY) : Sprite(path, spriteName, x, y, sizeX, sizeY) {

	}

	Background* Background::getInstance(const char* path, std::string spriteName, int x, int y, int sizeX, int sizeY) {
		return new Background(path, spriteName, x, y, sizeX, sizeY);
	}

}