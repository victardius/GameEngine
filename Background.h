#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Sprite.h"

namespace gameEngine {

	class Background : public Sprite {
	public:
		static Background* getInstance(Animator* animat, std::string spriteName, int x, int y);
	protected:
		Background(Animator* animat, std::string spriteName, int x, int y);
	private:
	};

}

#endif