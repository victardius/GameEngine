#include "Text.h"

namespace gameEngine {

	Text::Text(Animator* animat, std::string spriteName, int posX, int posY) : Sprite(animat, spriteName, posX, posY)
	{
	}

	Text* Text::getInstance(Animator* animat, std::string spriteName, int posX, int posY) {
		return this;
	}

}