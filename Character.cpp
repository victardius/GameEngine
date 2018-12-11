#include <cmath>
#include "Character.h"
#include "GameController.h"

#define PI 3.14159265

namespace gameEngine {

	Character::Character(int pHealth, int pSpeed, const char* path, std::string spriteName, int x, int y, int sizeX, int sizeY) : CollisionSprite(path, spriteName, x, y, sizeX, sizeY), health(pHealth), speed(pSpeed) {

	}

	Character* Character::getInstance(int pHealth, int pSpeed, const char* path, std::string spriteName, int x, int y, int sizeX, int sizeY) {
		return new Character(pHealth, pSpeed, path, spriteName, x, y, sizeX, sizeY);
	}

	void Character::tick() {
		move();
		rdrCpy();
	}

	void Character::move() {
		if (moveTargetX >= 0 && moveTargetY >= 0) {

			int distX = moveTargetX - getRect()->x;
			int distY = moveTargetY - getRect()->y;

			getRect()->x += directionX * speed;
			getRect()->y += directionY * speed;

			if (std::sqrt(std::pow(getRect()->x - startX, 2) + std::pow(getRect()->y - startY, 2)) >= distance)
			{
				stop();
			}
		}
	}

	void Character::stop() {		
		moveTargetX = -1;
		moveTargetY = -1;
	}

	void Character::moveTarget() {
		SDL_Rect* b;
		b = gc.getMPos();
		moveTargetX = b->x + (b->w / 2) - (getRect()->w / 2);
		moveTargetY = b->y + (b->h / 2) - (getRect()->h / 2);
		startX = getRect()->x;
		startY = getRect()->y;
		distance = std::sqrt(std::pow(moveTargetX - startX, 2) + std::pow(moveTargetY - startY, 2));
		directionX = (moveTargetX - startX) / distance;
		directionY = (moveTargetY - startY) / distance;
		focusX = moveTargetX + directionX * 100;
		focusY = moveTargetY + directionY * 100;
	}

	void Character::shoot() {
		stop();
		SDL_Rect* b;
		b = gc.getMPos();
		focusX = b->x;
		focusY = b->y;
		std::cout << "pew pew" << std::endl;
	}

	double Character::getSpeed() {
		return speed;
	}

	void Character::collisionEvent() {
		std::cout << "Kollision!" << std::endl;
	}

	void Character::setSpeed(int amount) {
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
		double angle = atan2(focusY - y, focusX - x) * 180 / PI;
		SDL_RenderCopyEx(gc.getRen(), getTx(), NULL, getRect(), angle, NULL, SDL_FLIP_NONE);
	}

}