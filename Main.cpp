#include "GameController.h"
#include "Character.h"
#include "Player.h"
#include <functional>

using namespace gameEngine;


std::shared_ptr<Player> player;
std::shared_ptr<Text> button;
std::shared_ptr<Level> level1;
std::shared_ptr<Level> level2;

void quit() {
	gc.quit();
}

void next() {
	gc.setLevel(level2);
	level1.reset();
	player->reset();
}

int main(int argc, char** argv)
{
	player = Player::getInstance(100, 5, Animator::getInstance("PNG/survivor 1/survivor1_gun_sheet.png", 52, 52, 8), "player", 250, 250, 0, 0, 10);
	button = Text::getInstance(Animator::getInstance("PNG/tiles/tile_538.png"), "Menu", "Menu", "Fonts/arial.ttf", new SDL_Color{ 50,50,50,255 }, 26, 550, 25);
	level1 = Level::getInstance();
	level1->createBG(100, Animator::getInstance("PNG/tiles/tile_01.png"));
	level1->addCollisionSprite(Character::getInstance(100, 50, Animator::getInstance("PNG/Man Brown/manBrown_stand.png"), "Brown", 500, 500));
	level1->addCollisionSprite(player);
	level1->addText(Text::getInstance(NULL, "Hello", "Level1", "Fonts/arial.ttf", new SDL_Color{200,0,0,255}, 30, 50, 50));
	level1->addText(button);
	level2 = Level::getInstance();
	level2->createBG(100, Animator::getInstance("PNG/tiles/tile_05.png"));
	level2->addCollisionSprite(Character::getInstance(100, 50, Animator::getInstance("PNG/Man Brown/manBrown_gun.png"), "Brown", 500, 500));
	level2->addCollisionSprite(player);
	level2->addText(Text::getInstance(NULL, "Hello", "Level2", "Fonts/arial.ttf", new SDL_Color{ 200,0,0,255 }, 30, 50, 50));
	level2->addText(button);
	gc.setLevel(level1);
	gc.addFunction(SDL_BUTTON_RIGHT, std::bind(&Player::moveTarget, player));
	gc.addFunction(SDL_BUTTON_LEFT, std::bind(&Player::shoot, player));
	gc.addFunction(SDLK_ESCAPE, quit/*std::bind(&GameController::quit, gc)*/);
	gc.addFunction(SDLK_RETURN, std::bind(&Text::setActive, button));
	gc.addFunction(SDLK_END, next);
	gc.setFPS(60);
	gc.start();
	return 0;
}

