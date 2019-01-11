#include "LevelManager.h"
#include "GameController.h"


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
	if (n == 0)
		nextLevel();
}

void LevelManager::addGoalText(std::shared_ptr<Text> t) {
	goal = t;
}

void LevelManager::start() {
	if (amountLevels > currentLevel)
		gc.setLevel(levels[++currentLevel]);
	levels[currentLevel]->addText(goal);
	gc.start();
}

void LevelManager::nextLevel() {
	if (amountLevels > currentLevel) {
		levels[currentLevel + 1]->addText(goal);
		gc.setLevel(levels[++currentLevel]);
	}
}

LevelManager::~LevelManager()
{
	levels.clear();
}

LevelManager lvlMngr;