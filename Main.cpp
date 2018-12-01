#include "GameController.h"

using namespace gameEngine;

int main(int argc, char** argv)
{

	gc.createBG(100, "PNG/tiles/tile_01.png");
	gc.addPlayer(100, 50, "PNG/survivor 1/survivor1_gun.png", "player", 250, 250);
	gc.eventHandler();

	return 0;
}

