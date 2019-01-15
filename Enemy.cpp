#include "Enemy.h"
#include "GameController.h"
#include "LevelManager.h"



Enemy::Enemy(double size, SDL_Point* p1, SDL_Point* p2, int pHealth, int pSpeed, std::shared_ptr<gameEngine::Animator> animat, std::string spriteName, int x, int y, int horizDrag, int vertDrag, int bounce) : MovingObject(pHealth, pSpeed, animat, spriteName, x, y, horizDrag, vertDrag, bounce), pStart(p1), pEnd(p2)
{
	animCount = gameEngine::gc.getFPS() / 5;
	changeSize(size);
}

std::shared_ptr<Enemy> Enemy::getInstance(double size, SDL_Point* p1, SDL_Point* p2, int pHealth, int pSpeed, std::shared_ptr<gameEngine::Animator> animat, std::string spriteName, int x, int y, int horizDrag, int vertDrag, int bounce) {
	return std::shared_ptr<Enemy>(new Enemy(size, p1, p2, pHealth, pSpeed, animat, spriteName, x, y, horizDrag, vertDrag, bounce));
}

void Enemy::tickFunction() {
	if (toAdd) {
		enemies++;
		lvlMngr.setGoal(enemies);
		toAdd = false;
	}
	if (dmgCooldown > 0)
		dmgCooldown--;
	if (getMoveTarget()->x == -1 && getMoveTarget()->y == -1) {
		patrol = !patrol;
		if (!patrol)
			moveTarget(pEnd);
		else
			moveTarget(pStart);
	}
	if (--animCount == 0) {
		if (frameToLoad > 5)
			frameToLoad = 0;
		if (!patrol)
			changeFrame(frameToLoad++);
		else
			changeFrame((frameToLoad++) + 6);
		animCount = gameEngine::gc.getFPS() / 5;
	}
	move();
}

void Enemy::setPatrol(SDL_Point* p1, SDL_Point* p2) {
	pStart = p1;
	pEnd = p2;
}

void Enemy::collisionEvent(std::shared_ptr<CollisionSprite> cs) {
	if (cs->getName() == "Bullet" && !dmgCooldown) {
		dmgCooldown = gameEngine::gc.getFPS() / 2;
		takeDamage(100);
	}
}

void Enemy::deathEvent() {
	enemies--;
	lvlMngr.setGoal(enemies);
	gameEngine::gc.getLevel()->removeCollidingObject(shared_from_this());
}

int Enemy::getEnemies() {
	return enemies;
}

Enemy::~Enemy()
{
	delete pStart;
	delete pEnd;
}
