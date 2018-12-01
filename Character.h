#ifndef CHARACTER_H
#define CHARACTER_H

#include "Sprite.h"
#include "Background.h"

namespace gameEngine {

	class Character : public Sprite {
	public:
		static Character* getInstance(int pHealth, double pSpeed, const char* path, int x, int y, int sizeX, int sizeY);
		void moving(SDL_Rect* b);
		void shoot(SDL_Rect* b); //add weapon later
		void takeDamage(int amount);
		int getHealth();
		double getSpeed();
		void setHealth(int amount);
		void setSpeed(double amount);
		void increaseHealth(int amount);
		void increaseSpeed(double amount);
		void rdrCpy();
	protected:
		Character(int pHealth, double pSpeed, const char* path, int x, int y, int sizeX, int sizeY);
	private:
		int health;
		double speed;
		int move(SDL_Rect* b);
		int targetX = 0, targetY = 0;
	};

}

#endif
