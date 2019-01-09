#include "GameController.h"
#include "Character.h"
#include "Player.h"
#include <functional>

using namespace gameEngine;


std::shared_ptr<Player> player;
std::shared_ptr<Text> button;

//void movePlayer() {
//	player->moveTarget();
//	button->setActive();
//}
//
//void shootPlayer() {
//	player->shoot();
//	button->setActive();
//}

void quit() {
	gc.quit();
}

int main(int argc, char** argv)
{
	player = Player::getInstance(100, 5, Animator::getInstance("PNG/survivor 1/survivor1_gun_sheet.png", 52, 52, 8), "player", 250, 250);
	button = Text::getInstance(Animator::getInstance("PNG/tiles/tile_538.png"), "Menu", "Menu", "Fonts/arial.ttf", new SDL_Color{ 50,50,50,255 }, 26, 550, 25);
	gc.createBG(100, Animator::getInstance("PNG/tiles/tile_01.png", 64, 64, 1));
	gc.addCollisionSprite(Character::getInstance(100, 50, Animator::getInstance("PNG/Man Brown/manBrown_stand.png"), "Brown", 500, 500));
	gc.addCollisionSprite(player);
	gc.addText(Text::getInstance(NULL, "Hello", "Hello", "Fonts/arial.ttf", new SDL_Color{200,0,0,255}, 30, 50, 50));
	gc.addText(button);
	gc.addFunction(SDL_BUTTON_RIGHT, std::bind(&Player::moveTarget, player));
	gc.addFunction(SDL_BUTTON_LEFT, std::bind(&Player::shoot, player));
	//gc.addFunction(SDLK_ESCAPE, std::bind(&GameController::quit, gc));
	gc.addFunction(SDLK_END, std::bind(&Text::setActive, button));
	gc.setFPS(60);
	gc.start();
	return 0;
}

