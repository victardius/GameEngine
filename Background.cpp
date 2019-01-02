#include "Background.h"
#include "GameController.h"

namespace gameEngine {

	Background::Background(Animator* animat, std::string spriteName, int x, int y) : Sprite(animat, spriteName, x, y) {

	}

	Background* Background::getInstance(Animator* animat, std::string spriteName, int x, int y) {
		return new Background(animat, spriteName, x, y);
	}

	void Background::tickFunction() {

	}

}