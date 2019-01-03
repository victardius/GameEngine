#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Sprite.h"

namespace gameEngine {

	class Background : public Sprite {
	public:
		static std::shared_ptr<Background> getInstance(std::shared_ptr<Animator> animat, std::string spriteName, int x, int y);
	protected:
		Background(std::shared_ptr<Animator> animat, std::string spriteName, int x, int y);
		virtual void tickFunction();
	private:
	};

}

#endif