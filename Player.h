#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"

using namespace gameEngine;

class Player : public Character {
public:
	static std::shared_ptr<Player> getInstance(int pHealth, int pSpeed, std::shared_ptr<Animator> animat, std::string spriteName, int x, int y);
	~Player();
protected:
	Player(int pHealth, int pSpeed, std::shared_ptr<Animator> animat, std::string spriteName, int x, int y);
	virtual void tickFunction();
private:
	void angleToFrame();
};

#endif

