#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"

using namespace gameEngine;

class Player : public Character {
public:
	static Player* getInstance(int pHealth, int pSpeed, Animator* animat, std::string spriteName, int x, int y);
	~Player();
	void tick();
protected:
	Player(int pHealth, int pSpeed, Animator* animat, std::string spriteName, int x, int y);
private:
	void angleToFrame();
};

#endif

