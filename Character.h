#ifndef CHARACTER_H
#define CHARACTER_H

#include "CollisionSprite.h"
#include "Background.h"

namespace gameEngine {

	class Character : public CollisionSprite {
	public:
		static Character* getInstance(int pHealth, int pSpeed, const char* path, std::string spriteName, int x, int y, int sizeX, int sizeY);
		void moveTarget(SDL_Rect* b);
		void shoot(SDL_Rect* b); //add weapon later
		void takeDamage(int amount);
		int getHealth();
		double getSpeed();
		void setHealth(int amount);
		void setSpeed(int amount);
		void tick();
	protected:
		Character(int pHealth, int pSpeed, const char* path, std::string spriteName, int x, int y, int sizeX, int sizeY);
		void collisionEvent();
	private:
		int health;
		int speed;
		int startX, startY;
		double distance, directionX, directionY;
		void move();
		int moveTargetX = -1, moveTargetY = -1, focusX = 0, focusY = 0;
		void rdrCpy();
		void stop();
	};

}

#endif
