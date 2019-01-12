#include "LevelManager.h"

using namespace gameEngine;

void instanciateGame();

int main(int argc, char** argv)
{
	instanciateGame();
	return 0;
}

void instanciateGame() {
	lvlMngr.start();
}