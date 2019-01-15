#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include "CollisionSprite.h"
#include "Animator.h"
#include "Coordinate.h"
#include <memory>

	class MovingObject : public gameEngine::CollisionSprite {
	public:
		void moveTarget(SDL_Point* p);
		void takeDamage(int amount);
		int getHealth();
		double getSpeed();
		void setHealth(int amount);
		void setSpeed(int amount);
		void setFocus(int x, int y);
		std::shared_ptr<Coordinate> getFocus();
		std::shared_ptr<Coordinate> getMoveTarget();
		~MovingObject();
	protected:
		MovingObject(int pHealth, int pSpeed, std::shared_ptr<gameEngine::Animator> animat, std::string spriteName, int x, int y, int horizDrag, int vertDrag, int bounce);
		void collisionEvent(std::shared_ptr<CollisionSprite> cs);
		void move();
		virtual void tickFunction();
		virtual void deathEvent() = 0;
		void stop();
	private:
		int counter = 0;
		int health;
		int speed;
		int startX, startY;
		double distance, directionX, directionY;
		int focusX = 0, focusY = 0;
		std::shared_ptr<Coordinate> focus, moveTargetPos;
	};

#endif
