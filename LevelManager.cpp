#include "LevelManager.h"
#include "GameController.h"

int Enemy::enemies = 0;

LevelManager::LevelManager()
{
}

void LevelManager::addLevel(std::shared_ptr<Level> l, std::shared_ptr<Animator> b, std::shared_ptr<Player> p) {
	amountLevels++;
	levels[amountLevels] = l;
	levels[amountLevels]->createBG(100, b);
	levels[amountLevels]->addCollisionSprite(p);
}

std::shared_ptr<Level> LevelManager::getLevel(int n) {
	if (levels.count(n))
		return levels[n];
	return nullptr;
}

void LevelManager::removeLevel(int n) {
	levels.erase(n);
}

void LevelManager::setGoal(int n) {
	goal->setText("Enemies Left: " + std::to_string(n));
	if (n == 0) {
		nextLevel();
	}
}

void LevelManager::addGoalText(std::shared_ptr<Text> t) {
	goal = t;
}

void LevelManager::start() {
	player = Player::getInstance(100, 5, Animator::getInstance("PNG/survivor 1/survivor1_gun_sheet.png", 52, 52, 8), "Player", 100, 100, 100, 0, 20);
	lifeText = Text::getInstance(Animator::getInstance("PNG/tiles/tile_538.png"), "Life", "100", "Fonts/arial.ttf", new SDL_Color{ 155,50,50,255 }, 26, 550, 25);
	addLevels();
	if (amountLevels > currentLevel)
		gc.setLevel(levels[++currentLevel]);
	levels[currentLevel]->addText(goal);
	KeyManager::getInstance();
	gc.setFPS(60);
	gc.start();
}

void LevelManager::nextLevel() {
	if (amountLevels > currentLevel) {
		levels[currentLevel + 1]->addText(goal);
		gc.setLevel(levels[++currentLevel]);
	}
}

void LevelManager::addLevels() {
	lvlMngr.addGoalText(Text::getInstance(Animator::getInstance("PNG/tiles/tile_538.png"), "Enemies", " ", "Fonts/arial.ttf", new SDL_Color{ 50,50,50,255 }, 26, 320, 25));
	addLevel1();
	addLevel2();
	addFinalScene();
	player->setLifeBar(lifeText);
}

void LevelManager::addLevel1() {
	addLevel(Level::getInstance(), Animator::getInstance("PNG/tiles/tile_01.png"), player);
	getLevel(1)->addCollisionSprite(Enemy::getInstance(0.8, new SDL_Point{ 500, 500 }, new SDL_Point{ 500, 250 }, 100, 3, Animator::getInstance("PNG/bkspr02.png", 132, 139, 12), "Enemy", 434, 430));
	getLevel(1)->addCollisionSprite(Enemy::getInstance(0.8, new SDL_Point{ 300, 300 }, new SDL_Point{ 300, 100 }, 100, 7, Animator::getInstance("PNG/bkspr02.png", 132, 139, 12), "Enemy", 234, 230));
	getLevel(1)->addCollisionSprite(Enemy::getInstance(0.8, new SDL_Point{ 100, 550 }, new SDL_Point{ 150, 350 }, 100, 4, Animator::getInstance("PNG/bkspr02.png", 132, 139, 12), "Enemy", 34, 480));
	getLevel(1)->addText(Text::getInstance(NULL, "Hello", "Level1", "Fonts/arial.ttf", new SDL_Color{ 70,70,70,255 }, 30, 50, 50));
	getLevel(1)->addText(lifeText);
}

void LevelManager::addLevel2() {
	addLevel(Level::getInstance(), Animator::getInstance("PNG/tiles/tile_05.png"), player);
	getLevel(2)->addCollisionSprite(Enemy::getInstance(0.8, new SDL_Point{ 500, 500 }, new SDL_Point{ 500, 250 }, 100, 3, Animator::getInstance("PNG/bkspr02.png", 132, 139, 12), "Enemy", 434, 430));
	getLevel(2)->addText(Text::getInstance(NULL, "Hello", "Level2", "Fonts/arial.ttf", new SDL_Color{ 70,70,70,255 }, 30, 50, 50));
	getLevel(2)->addText(lifeText);
}

void LevelManager::addFinalScene() {
	addLevel(Level::getInstance(), Animator::getInstance("PNG/tiles/tile_86.png"), player);
	getLevel(3)->addText(Text::getInstance(NULL, "Last", "You won!", "Fonts/arial.ttf", new SDL_Color{ 70,120,70,255 }, 30, 270, 305));
	finalText = Text::getInstance(NULL, "LastLast", "Press return to type your name here!", "Fonts/arial.ttf", new SDL_Color{ 70,120,70,255 }, 30, 170, 335);
	getLevel(3)->addText(finalText);
}

std::shared_ptr<Player> LevelManager::getPlayer() {
	return player;
}

std::shared_ptr<Text> LevelManager::getFinalText() {
	return finalText;
}

LevelManager::~LevelManager()
{
	levels.clear();
}

LevelManager lvlMngr;