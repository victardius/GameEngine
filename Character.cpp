#include "Character.h"
#include "GameController.h"

using namespace gameEngine;

	Character::Character(int pHealth, int pSpeed, std::shared_ptr<Animator> animat, std::string spriteName, int x, int y, int horizDrag, int vertDrag, int bounce) : CollisionSprite(animat, spriteName, x, y, horizDrag, vertDrag, bounce), health(pHealth), speed(pSpeed) {
		focus = std::shared_ptr<Coordinate>(new Coordinate(0, 0));
	}

	std::shared_ptr<Character> Character::getInstance(int pHealth, int pSpeed, std::shared_ptr<Animator> animat, std::string spriteName, int x, int y, int horizDrag, int vertDrag, int bounce) {
		return std::shared_ptr<Character>(new Character(pHealth, pSpeed, animat, spriteName, x, y, horizDrag, vertDrag, bounce));
	}

	void Character::tickFunction() {
		move();
	}

	void Character::move() {
		if (moveTargetX >= 0 && moveTargetY >= 0) {

			movePos((int)(directionX * speed), (int)(directionY * speed));

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
		focus->x = (int)(moveTargetX + directionX * 100);
		focus->y = (int)(moveTargetY + directionY * 100);
	}

	void Character::shoot() {
		stop();
		SDL_Rect* b;
		b = gc.getMPos();
		focus->x = b->x;
		focus->y = b->y;
		std::cout << "pew pew" << std::endl;
	}

	double Character::getSpeed() {
		return speed;
	}

	void Character::collisionEvent(std::shared_ptr<CollisionSprite> cs) {
		//std::cerr << "Kollision!" << std::endl;
		std::cerr << ++counter << std::endl;
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

	std::shared_ptr<Coordinate> Character::getFocus() {
		return focus;
	}

	Character::~Character() {
		focus.reset();
	}