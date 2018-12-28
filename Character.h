#ifndef CHARACTER_H
#define CHARACTER_H

#include "CollisionSprite.h"
#include "Background.h"
#include "Animator.h"
#include "Coordinate.h"

using namespace gameEngine;

	class Character : public CollisionSprite {
	public:
		static Character* getInstance(int pHealth, int pSpeed, Animator* animat, std::string spriteName, int x, int y);
		void moveTarget();
		void shoot(); //add weapon later
		void takeDamage(int amount);
		int getHealth();
		double getSpeed();
		void setHealth(int amount);
		void setSpeed(int amount);
		void tick();
		Coordinate* getFocus();
	protected:
		Character(int pHealth, int pSpeed, Animator* animat, std::string spriteName, int x, int y);
		void collisionEvent();
		void move();
	private:
		int health;
		int speed;
		int startX, startY;
		double distance, directionX, directionY;
		int moveTargetX = -1, moveTargetY = -1, focusX = 0, focusY = 0;
		void stop();
	};

#endif
