#include "Player.h"
#include "GameController.h"
#include "Bullet.h"
#include <cmath>
#include <string>

#define PI 3.14159265

using namespace gameEngine;

Player::Player(int pHealth, int pSpeed, std::shared_ptr<Animator> animat, std::string spriteName, int x, int y, int horizDrag, int vertDrag, int bounce) : MovingObject(pHealth, pSpeed, animat, spriteName, x, y, horizDrag, vertDrag, bounce)
{
	startPos = { x,y };
	startHealth = pHealth;
	startSpeed = pSpeed;
}

std::shared_ptr<Player> Player::getInstance(int pHealth, int pSpeed, std::shared_ptr<Animator> animat, std::string spriteName, int x, int y, int horizDrag, int vertDrag, int bounce) {
	return std::shared_ptr<Player>(new Player(pHealth, pSpeed, animat, spriteName, x, y, horizDrag, vertDrag, bounce));
}

void Player::tickFunction() {
	if (dmgCooldown > 0)
		dmgCooldown--;
	move();
	bouncing();
	angleToFrame();
	lifeBar->setText(std::to_string(getHealth()));
}

void Player::collisionEvent(std::shared_ptr<CollisionSprite> cs) {
	if (cs->getName() == "Enemy" && !dmgCooldown) {
		bounce(new SDL_Point{ cs->getRect()->x, cs->getRect()->y });
		dmgCooldown = gc.getFPS() / 2;
		takeDamage(20);
		stop();
	}
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

void Player::moveTo() {
	moveTarget(gc.getMPos());
}

void Player::shoot() {
	stop();
	setFocus(gc.getMPos()->x, gc.getMPos()->y);
	gc.getLevel()->addCollisionSprite(Bullet::getInstance(100, 10, Animator::getInstance("PNG/Bullet.png"), "Bullet", getRect()->x, getRect()->y));
}

void Player::setLifeBar(std::shared_ptr<Text> t) {
	lifeBar = t;
}

void Player::reset() {
	*getPosition() = startPos;
	setHealth(startHealth);
	setSpeed(startSpeed);
}

void Player::deathEvent() {
	reset();
}

Player::~Player()
{
}
