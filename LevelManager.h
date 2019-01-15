#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "KeyManager.h"
#include "Text.h"
#include <map>
#include <string>

class LevelManager
{
public:
	void addLevel(std::shared_ptr<gameEngine::Level> l, std::shared_ptr<gameEngine::Animator> b, std::shared_ptr<Player> p);
	std::shared_ptr<gameEngine::Level> getLevel(int k);
	void removeLevel(int n);
	void start();
	LevelManager();
	void nextLevel();
	void setGoal(int n);
	void addGoalText(std::shared_ptr<gameEngine::Text> t);
	void addLevels();
	std::shared_ptr<Player> getPlayer();
	std::shared_ptr<gameEngine::Text> getFinalText();
	~LevelManager();
protected:
private:
	std::map<int, std::shared_ptr<gameEngine::Level>> levels;
	int currentLevel = 0, amountLevels = 0, enemiesLeft;
	std::shared_ptr<gameEngine::Text> goal;
	void addLevel1();
	void addLevel2();
	void addFinalScene();
	void createBG(int amount, std::shared_ptr<gameEngine::Animator> animat, std::shared_ptr<gameEngine::Level> l);
	std::shared_ptr<Player> player;
	std::shared_ptr<gameEngine::Text> lifeText;
	std::shared_ptr<gameEngine::Text> finalText;
};

extern LevelManager lvlMngr;

#endif