#include "Player.h"
#include "GameController.h"
#include <cmath>
#define PI 3.14159265

using namespace gameEngine;

Player::Player(int pHealth, int pSpeed, std::shared_ptr<Animator> animat, std::string spriteName, int x, int y, int horizDrag, int vertDrag, int bounce) : Character(pHealth, pSpeed, animat, spriteName, x, y, horizDrag, vertDrag, bounce)
{
	startPos = { x,y };
	startHealth = pHealth;
	startSpeed = pSpeed;
}

std::shared_ptr<Player> Player::getInstance(int pHealth, int pSpeed, std::shared_ptr<Animator> animat, std::string spriteName, int x, int y, int horizDrag, int vertDrag, int bounce) {
	return std::shared_ptr<Player>(new Player(pHealth, pSpeed, animat, spriteName, x, y, horizDrag, vertDrag, bounce));
}

void Player::tickFunction() {
	move();
	bouncing();
	angleToFrame();
	rdrCpy();
}

void Player::collisionEvent(std::shared_ptr<CollisionSprite> cs) {
	bounce(new SDL_Point{ cs->getRect()->x, cs->getRect()->y });
	stop();
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
		changeFrame((int)a);
}

void Player::reset() {
	*getPosition() = startPos;
	setHealth(startHealth);
	setSpeed(startSpeed);
}

Player::~Player()
{
}
