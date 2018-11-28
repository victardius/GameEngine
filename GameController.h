#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SDL.h>
#include <unordered_map>
#include <string>
#include "Texture.h"

class GameController {
public:
	void init();
	void eventHandler();
	void addTexture(const char* path, std::string name, int x = 0, int y = 0, int sizeX = 0, int sizeY = 0);
	void end();
private:
	std::unordered_map<std::string, Texture*> textures;
	SDL_Window* win;
	SDL_Renderer* ren;
	void renderReset();
};

#endif
