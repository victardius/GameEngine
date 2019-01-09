#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"

using namespace gameEngine;

class Player : public Character {
public:
	static std::shared_ptr<Player> getInstance(int pHealth, int pSpeed, std::shared_ptr<Animator> animat, std::string spriteName, int x, int y, int horizDrag = 0, int vertDrag = 0, int bounce = 0);
	void reset();
	~Player();
protected:
	Player(int pHealth, int pSpeed, std::shared_ptr<Animator> animat, std::string spriteName, int x, int y, int horizDrag, int vertDrag, int bounce);
	virtual void tickFunction();
	virtual void collisionEvent(std::shared_ptr<CollisionSprite> cs);
private:
	void angleToFrame();
	SDL_Point startPos;
	int startHealth, startSpeed;
};

#endif

