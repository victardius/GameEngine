#ifndef CHARACTER_H
#define CHARACTER_H

#include "CollisionSprite.h"
#include "Animator.h"
#include "Coordinate.h"
#include <memory>

using namespace gameEngine;

	class Character : public CollisionSprite {
	public:
		static std::shared_ptr<Character> getInstance(int pHealth, int pSpeed, std::shared_ptr<Animator> animat, std::string spriteName, int x, int y, int horizDrag = 0, int vertDrag = 0, int bounce = 0);
		void moveTarget();
		void shoot(); //add weapon later
		void takeDamage(int amount);
		int getHealth();
		double getSpeed();
		void setHealth(int amount);
		void setSpeed(int amount);
		std::shared_ptr<Coordinate> getFocus();
		~Character();
	protected:
		Character(int pHealth, int pSpeed, std::shared_ptr<Animator> animat, std::string spriteName, int x, int y, int horizDrag, int vertDrag, int bounce);
		void collisionEvent(std::shared_ptr<CollisionSprite> cs);
		void move();
		virtual void tickFunction();
		void stop();
	private:
		int counter = 0;
		int health;
		int speed;
		int startX, startY;
		double distance, directionX, directionY;
		int moveTargetX = -1, moveTargetY = -1, focusX = 0, focusY = 0;
		std::shared_ptr<Coordinate> focus;
	};

#endif
