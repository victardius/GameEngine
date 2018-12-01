#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Sprite.h"

namespace gameEngine {

	class Background : public Sprite {
	public:
		static Background* getInstance(const char* path, int x, int y, int sizeX, int sizeY);
	protected:
		Background(const char* path, int x, int y, int sizeX, int sizeY);
	private:
	};

}

#endif