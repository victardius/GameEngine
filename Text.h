#ifndef TEXT_H
#define TEXT_H

#include "Sprite.h"

namespace gameEngine {

	class Text : public Sprite
	{
	public:
		Text* getInstance(const char* path, std::string spriteName, int posX = 0, int posY = 0, int sizeW = 0, int sizeH = 0);
	protected:
		Text(const char* path, std::string spriteName, int posX, int posY, int sizeW, int sizeH);
	};

}

#endif

