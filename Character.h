#ifndef CHARACTER_H
#define CHARACTER_H

#include "Sprite.h"
#include "Background.h"

class Character : public Sprite {
public:
	Character(int pHealth, double pSpeed, const char* path, SDL_Renderer* rdr, int x, int y, int sizeX, int sizeY) : Sprite(path, rdr, x, y, sizeX, sizeY), health(pHealth), speed(pSpeed) {}
	int move(SDL_Rect* b);
	void shoot(int x, int y); //add weapon later
	void takeDamage(int amount);
	int getHealth();
	double getSpeed();
	void setHealth(int amount);
	void setSpeed(double amount);
	void increaseHealth(int amount);
	void increaseSpeed(double amount);
private:
	int health;
	double speed;
};

#endif
