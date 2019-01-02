#include "Character.h"
#include "GameController.h"

using namespace gameEngine;

	Character::Character(int pHealth, int pSpeed, Animator* animat, std::string spriteName, int x, int y) : CollisionSprite(animat, spriteName, x, y), health(pHealth), speed(pSpeed) {

	}

	Character* Character::getInstance(int pHealth, int pSpeed, Animator* animat, std::string spriteName, int x, int y) {
		return new Character(pHealth, pSpeed, animat, spriteName, x, y);
	}

	void Character::tickFunction() {
		move();
	}

	void Character::move() {
		if (moveTargetX >= 0 && moveTargetY >= 0) {

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
		std::cerr << "Kollision!" << std::endl;
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

	Coordinate* Character::getFocus() {
		return new Coordinate(focusX, focusY);
	}