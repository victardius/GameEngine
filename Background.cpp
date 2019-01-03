#include "Background.h"
#include "GameController.h"

namespace gameEngine {

	Background::Background(std::shared_ptr<Animator> animat, std::string spriteName, int x, int y) : Sprite(animat, spriteName, x, y) {

	}

	std::shared_ptr<Background> Background::getInstance(std::shared_ptr<Animator> animat, std::string spriteName, int x, int y) {
		return std::shared_ptr<Background>(new Background(animat, spriteName, x, y));
	}

	void Background::tickFunction() {

	}

}