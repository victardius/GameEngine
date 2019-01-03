#include "GameController.h"
#include "Character.h"
#include "Player.h"

using namespace gameEngine;


std::shared_ptr<Player> player;

void movePlayer() {
	player->moveTarget();
}

void shootPlayer() {
	player->shoot();
}

void quit() {
	gc.quit();
}

int main(int argc, char** argv)
{
	player = Player::getInstance(100, 5, Animator::getInstance("PNG/survivor 1/survivor1_gun_sheet.png", 52, 52, 8), "player", 250, 250);
	std::shared_ptr<Text> button = Text::getInstance(Animator::getInstance("PNG/tiles/tile_538.png"), "Menu", "Menu", "Fonts/arial.ttf", new SDL_Color{ 50,50,50,255 }, 26, 550, 25);
	gc.createBG(100, Animator::getInstance("PNG/tiles/tile_01.png", 64, 64, 1));
	gc.addCollisionSprite(Character::getInstance(100, 50, Animator::getInstance("PNG/Man Brown/manBrown_stand.png", 33, 43, 1), "Brown", 500, 500));
	gc.addCollisionSprite(player);
	gc.addText(Text::getInstance(NULL, "Hello", "Hello", "Fonts/arial.ttf", new SDL_Color{200,0,0,255}, 30, 50, 50));
	gc.addText(button);
	gc.addFunction(3, movePlayer);
	gc.addFunction(1, shootPlayer);
	gc.addFunction(27, quit);
	gc.start();
	return 0;
}

