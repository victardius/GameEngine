#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <string>
#include <iostream>
#include "Sprite.h"
#include "Character.h"

class GameController {
public:
	void init();
	void eventHandler();
	void addBackground(const char* path, std::string name, int x = 0, int y = 0, int sizeX = 0, int sizeY = 0);
	void addPlayer(int pHealth, double pSpeed, const char* path, std::string name, int x = 0, int y = 0, int sizeX = 0, int sizeY = 0);
	void end();
	void mouseClick(SDL_MouseButtonEvent mb, SDL_Point p);
	void renderReset();
private:
	std::unordered_map<std::string, Sprite*> sprites;
	std::unordered_map<std::string, Background*> bg;
	Character* player;
	SDL_Window* win;
	SDL_Renderer* ren;
};

#endif
