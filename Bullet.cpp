#include "Bullet.h"
#include "GameController.h"

Bullet::Bullet(int dmg, int speed, std::shared_ptr<gameEngine::Animator> animat, std::string spriteName, int x, int y, int horizDrag, int vertDrag, int bounce) : MovingObject(1, speed, animat, spriteName, x, y, horizDrag, vertDrag, bounce), damage(dmg)
{
	moveTarget(gameEngine::gc.getMPos());
	deathCounter = gameEngine::gc.getFPS();
}

std::shared_ptr<Bullet> Bullet::getInstance(int dmg, int speed, std::shared_ptr<gameEngine::Animator> animat, std::string spriteName, int x, int y, int horizDrag, int vertDrag, int bounce) {
	return std::shared_ptr<Bullet>(new Bullet(dmg, speed, animat, spriteName, x, y, horizDrag, vertDrag, bounce));
}

void Bullet::collisionEvent(std::shared_ptr<CollisionSprite> cs) {
	if (cs->getName() == "Enemy") {
		deathEvent();
	}
}

void Bullet::tickFunction() {
	move();
	if (!--deathCounter) {
		deathEvent();
	}
}

void Bullet::deathEvent() {
	gameEngine::gc.getLevel()->removeCollidingObject(shared_from_this());
}

Bullet::~Bullet()
{
}
