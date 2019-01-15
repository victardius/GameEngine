#include "KeyManager.h"
#include "GameController.h"

KeyManager::KeyManager()
{
	addKeys();
}

KeyManager* KeyManager::getInstance() {
	return new KeyManager();
}

void KeyManager::addKeys() {
	addKey(SDL_BUTTON_RIGHT, std::bind(&Player::moveTo, lvlMngr.getPlayer()));
	addKey(SDL_BUTTON_LEFT, std::bind(&Player::shoot, lvlMngr.getPlayer()));
	addKey(SDLK_ESCAPE, std::bind(&gameEngine::GameController::quit, &gameEngine::gc));
	addKey(SDLK_RETURN, std::bind(&gameEngine::Text::setActive, lvlMngr.getFinalText()));
}

void KeyManager::addKey(int a, std::function<void()> f) {
	gameEngine::gc.addFunction(a, f);
}

KeyManager::~KeyManager()
{
}
