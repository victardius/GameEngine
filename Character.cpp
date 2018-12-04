#include <cmath>
#include "Character.h"
#include "GameController.h"

#define PI 3.14159265

namespace gameEngine {

	Character::Character(int pHealth, double pSpeed, const char* path, std::string spriteName, int x, int y, int sizeX, int sizeY) : CollisionSprite(path, spriteName, x, y, sizeX, sizeY), health(pHealth), speed(pSpeed) {

	}

	Character* Character::getInstance(int pHealth, double pSpeed, const char* path, std::string spriteName, int x, int y, int sizeX, int sizeY) {
		return new Character(pHealth, pSpeed, path, spriteName, x, y, sizeX, sizeY);
	}

	int Character::move(SDL_Rect* b) {

		int distX;
		int distY;

		distX = (b->x + (b->w / 2) - (getRect()->w / 2)) - getRect()->x;
		distY = (b->y + (b->h / 2) - (getRect()->h / 2)) - getRect()->y;

		if (distX > 0) {
			getRect()->x++;
		}
		else if (distX < 0) {
			getRect()->x--;
		}

		if (distY > 0) {
			getRect()->y++;
		}
		else if (distY < 0) {
			getRect()->y--;
		}

		

		return distX + distY;

	}

	void Character::moving(SDL_Rect* b) {
		while (move(b) != 0) {
			targetX = b->x;
			targetY = b->y;
			gc.renderReset();
			double delay = 100 / speed;
			SDL_Delay(delay);
		}
	}

	void Character::shoot(SDL_Rect* b) {
		targetX = b->x;
		targetY = b->y;
		gc.renderReset();
		std::cout << "pew pew" << std::endl;
	}

	double Character::getSpeed() {
		return speed;
	}

	void Character::setSpeed(double amount) {
		speed = amount;
	}

	void Character::takeDamage(int amount) {
		health -= amount;
		if (health <= 0) {
			std::cout << "dead" << std::endl;
		}
	}

	int Character::getHealth() {
		return health;
	}

	void Character::setHealth(int amount) {
		health = amount;
	}

	void Character::rdrCpy() {
		int x = getRect()->x;
		int y = getRect()->y;
		double angle = atan2(targetY - y, targetX - x) * 180 / PI;
		SDL_RenderCopyEx(gc.getRen(), getTx(), NULL, getRect(), angle, NULL, SDL_FLIP_NONE);
	}

}