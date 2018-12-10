#include "Text.h"

namespace gameEngine {

	Text::Text(const char* path, std::string spriteName, int posX, int posY, int sizeW, int sizeH) : Sprite(path, spriteName, posX, posY, sizeW, sizeH)
	{
	}

	Text* Text::getInstance(const char* path, std::string spriteName, int posX, int posY, int sizeW, int sizeH) {
		return this;
	}

}