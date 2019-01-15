#ifndef KEYMANAGER_H
#define KEYMANAGER_H

#include <functional>
#include "Player.h"
#include "LevelManager.h"

class KeyManager
{
public:
	static KeyManager* getInstance();
	void addKeys();
	~KeyManager();
protected:
	KeyManager();
private:
	void addKey(int a, std::function<void()> f);
};

#endif