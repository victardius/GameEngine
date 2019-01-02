#include "Player.h"
#include "GameController.h"
#include <cmath>
#define PI 3.14159265

using namespace gameEngine;

Player::Player(int pHealth, int pSpeed, Animator* animat, std::string spriteName, int x, int y) : Character(pHealth, pSpeed, animat, spriteName, x, y)
{
}

Player* Player::getInstance(int pHealth, int pSpeed, Animator* animat, std::string spriteName, int x, int y) {
	return new Player(pHealth, pSpeed, animat, spriteName, x, y);
}

void Player::tickFunction() {
	move();
	angleToFrame();
	rdrCpy();
}

void Player::angleToFrame() {
	int x = getRect()->x;
	int y = getRect()->y;
	double angle = atan2(getFocus()->y - y, getFocus()->x - x) * 180 / PI;
	if (angle < 0)
		angle += 360;
	double a = 360 / getAnimation()->getFrames();
	a = angle / a;
	a = round(a);
	if (a == getAnimation()->getFrames())
		changeFrame(0);
	else
		changeFrame(a);
}

Player::~Player()
{
}
