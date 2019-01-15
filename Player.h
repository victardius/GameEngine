#ifndef PLAYER_H
#define PLAYER_H

#include "MovingObject.h"
#include "Text.h"

class Player : public MovingObject {
public:
	static std::shared_ptr<Player> getInstance(int pHealth, int pSpeed, std::shared_ptr<gameEngine::Animator> animat, std::string spriteName, int x, int y, int horizDrag = 0, int vertDrag = 0, int bounce = 0);
	void reset();
	void moveTo();
	void shoot();
	void setLifeBar(std::shared_ptr<gameEngine::Text> t);
	~Player();
protected:
	Player(int pHealth, int pSpeed, std::shared_ptr<gameEngine::Animator> animat, std::string spriteName, int x, int y, int horizDrag, int vertDrag, int bounce);
	virtual void tickFunction();
	virtual void collisionEvent(std::shared_ptr<CollisionSprite> cs);
	virtual void deathEvent();
private:
	void angleToFrame();
	SDL_Point startPos;
	int startHealth, startSpeed, dmgCooldown = 0;
	std::shared_ptr<gameEngine::Text> lifeBar;
};

#endif

