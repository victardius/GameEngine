#include "GameController.h"
#include "Enemy.h"
#include "Player.h"
#include "LevelManager.h"
#include <functional>

using namespace gameEngine;

int Enemy::enemies = 0;

std::shared_ptr<Player> player;
std::shared_ptr<Text> text2;

void quit() {
	gc.quit();
}

//void next() {
//	gc.setLevel(level2);
//	level1.reset();
//	player->reset();
//	player->setVerticalDrag(100);
//}

int main(int argc, char** argv)
{
	player = Player::getInstance(100, 5, Animator::getInstance("PNG/survivor 1/survivor1_gun_sheet.png", 52, 52, 8), "Player", 100, 100, 100, 0, 20);
	text2 = Text::getInstance(Animator::getInstance("PNG/tiles/tile_538.png"), "Life", "100", "Fonts/arial.ttf", new SDL_Color{ 155,50,50,255 }, 26, 550, 25);
	lvlMngr.addGoalText(Text::getInstance(Animator::getInstance("PNG/tiles/tile_538.png"), "Enemies", " ", "Fonts/arial.ttf", new SDL_Color{ 50,50,50,255 }, 26, 320, 25));
	lvlMngr.addLevel(Level::getInstance(), Animator::getInstance("PNG/tiles/tile_01.png"), player);
	lvlMngr.getLevel(1)->addCollisionSprite(Enemy::getInstance(0.8, new SDL_Point{ 500, 500 }, new SDL_Point{ 500, 250 }, 100, 3, Animator::getInstance("PNG/bkspr02.png", 132, 139, 12), "Enemy", 434, 430));
	lvlMngr.getLevel(1)->addCollisionSprite(Enemy::getInstance(0.8, new SDL_Point{ 300, 300 }, new SDL_Point{ 300, 100 }, 100, 7, Animator::getInstance("PNG/bkspr02.png", 132, 139, 12), "Enemy", 234, 230));
	lvlMngr.getLevel(1)->addCollisionSprite(Enemy::getInstance(0.8, new SDL_Point{ 100, 550 }, new SDL_Point{ 150, 350 }, 100, 4, Animator::getInstance("PNG/bkspr02.png", 132, 139, 12), "Enemy", 34, 480));
	lvlMngr.getLevel(1)->addText(Text::getInstance(NULL, "Hello", "Level1", "Fonts/arial.ttf", new SDL_Color{70,70,70,255}, 30, 50, 50));
	lvlMngr.getLevel(1)->addText(text2);
	lvlMngr.addLevel(Level::getInstance(), Animator::getInstance("PNG/tiles/tile_05.png"), player);
	lvlMngr.getLevel(2)->addCollisionSprite(Enemy::getInstance(0.8, new SDL_Point{ 500, 500 }, new SDL_Point{ 500, 250 }, 100, 3, Animator::getInstance("PNG/bkspr02.png", 132, 139, 12), "Enemy", 434, 430));
	lvlMngr.getLevel(2)->addText(Text::getInstance(NULL, "Hello", "Level2", "Fonts/arial.ttf", new SDL_Color{ 70,70,70,255 }, 30, 50, 50));
	lvlMngr.getLevel(2)->addText(text2);
	player->setLifeBar(text2);
	gc.addFunction(SDL_BUTTON_RIGHT, std::bind(&Player::moveTo, player));
	gc.addFunction(SDL_BUTTON_LEFT, std::bind(&Player::shoot, player));
	gc.addFunction(SDLK_ESCAPE, quit);
	gc.addFunction(SDLK_RETURN, std::bind(&Text::setActive, text2));
	/*gc.addFunction(SDLK_END, next);*/
	gc.setFPS(60);
	lvlMngr.start();
	return 0;
}

