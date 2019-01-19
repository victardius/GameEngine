#include "MovingObject.h"
#include "GameController.h"

using namespace gameEngine;

	MovingObject::MovingObject(int pHealth, int pSpeed, std::shared_ptr<Animator> animat, std::string spriteName, int x, int y, int horizDrag, int vertDrag, int bounce) : CollisionSprite(animat, spriteName, x, y, horizDrag, vertDrag, bounce), health(pHealth), speed(pSpeed) {
		focus = std::shared_ptr<Coordinate>(new Coordinate(0, 0));
		moveTargetPos = std::shared_ptr<Coordinate>(new Coordinate(-1, -1));
	}

	void MovingObject::tickFunction() {
		move();
	}

	void MovingObject::move() {
		if (moveTargetPos->x >= 0 && moveTargetPos->y >= 0) {

			movePos((int)(directionX * speed), (int)(directionY * speed));

			if (std::sqrt(std::pow(getRect()->x - startX, 2) + std::pow(getRect()->y - startY, 2)) >= distance && getName() != "Bullet")
			{
				stop();
			}
		}
	}

	void MovingObject::stop() {		
		moveTargetPos->x = -1;
		moveTargetPos->y = -1;
	}

	void MovingObject::moveTarget(SDL_Point* p) {
		moveTargetPos->x = p->x - (getRect()->w / 2);
		moveTargetPos->y = p->y - (getRect()->h / 2);
		startX = getRect()->x;
		startY = getRect()->y;
		distance = std::sqrt(std::pow(moveTargetPos->x - startX, 2) + std::pow(moveTargetPos->y - startY, 2));
		directionX = (moveTargetPos->x - startX) / distance;
		directionY = (moveTargetPos->y - startY) / distance;
		focus->x = (int)(moveTargetPos->x + directionX * 100);
		focus->y = (int)(moveTargetPos->y + directionY * 100);
	}

	double MovingObject::getSpeed() const {
		return speed;
	}

	void MovingObject::collisionEvent(std::shared_ptr<CollisionSprite> cs) {
		std::cerr << ++counter << std::endl;
	}

	void MovingObject::setSpeed(int amount) {
		speed = amount;
	}

	void MovingObject::takeDamage(int amount) {
		health -= amount;
		if (health <= 0) {
			deathEvent();
		}
	}

	int MovingObject::getHealth() const {
		return health;
	}

	void MovingObject::setHealth(int amount) {
		health = amount;
	}

	void MovingObject::setFocus(int x, int y) {
		focus->x = x;
		focus->y = y;
	}

	std::shared_ptr<Coordinate> MovingObject::getFocus() const {
		return focus;
	}

	std::shared_ptr<Coordinate> MovingObject::getMoveTarget() const {
		return moveTargetPos;
	}

	MovingObject::~MovingObject() {
		focus.reset();
	}