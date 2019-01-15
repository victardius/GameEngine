#ifndef ENEMY_H
#define ENEMY_H
#include "MovingObject.h"

class Enemy : public MovingObject, public std::enable_shared_from_this<Enemy> {
public:
	static std::shared_ptr<Enemy> getInstance(double size, SDL_Point* p1, SDL_Point* p2, int pHealth, int pSpeed, std::shared_ptr<gameEngine::Animator> animat, std::string spriteName, int x, int y, int horizDrag = 0, int vertDrag = 0, int bounce = 0);
	void setPatrol(SDL_Point* p1, SDL_Point* p2);
	int getEnemies();
	~Enemy();
protected:
	Enemy(double size, SDL_Point* p1, SDL_Point* p2, int pHealth, int pSpeed, std::shared_ptr<gameEngine::Animator> animat, std::string spriteName, int x, int y, int horizDrag, int vertDrag, int bounce);
	virtual void tickFunction();
	virtual void collisionEvent(std::shared_ptr<CollisionSprite> cs);
	virtual void deathEvent();
private:
	int dmgCooldown = 0, animCount, frameToLoad = 0;
	SDL_Point* pStart,* pEnd;
	bool patrol = true;
	static int enemies;
	bool toAdd = true;
};

#endif

