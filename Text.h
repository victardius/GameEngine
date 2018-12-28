#ifndef TEXT_H
#define TEXT_H

#include "Sprite.h"

namespace gameEngine {

	class Text : public Sprite
	{
	public:
		Text* getInstance(Animator* animat, std::string spriteName, int posX = 0, int posY = 0);
	protected:
		Text(Animator* animat, std::string spriteName, int posX, int posY);
	};

}

#endif

