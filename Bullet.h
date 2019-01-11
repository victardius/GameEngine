#ifndef BULLET_H
#define BULLT_H

#include "MovingObject.h"

using namespace gameEngine;

class Bullet : public MovingObject, public std::enable_shared_from_this<Bullet>
{
public:
	static std::shared_ptr<Bullet> getInstance(int dmg, int speed, std::shared_ptr<Animator> animat, std::string spriteName, int x, int y, int horizDrag = 0, int vertDrag = 0, int bounce = 0);
	~Bullet();
protected:
	Bullet(int dmg, int speed, std::shared_ptr<Animator> animat, std::string spriteName, int x, int y, int horizDrag, int vertDrag, int bounce);
	virtual void tickFunction();
	virtual void collisionEvent(std::shared_ptr<CollisionSprite> cs);
	virtual void deathEvent();
private:
	int damage, deathCounter;
};

#endif