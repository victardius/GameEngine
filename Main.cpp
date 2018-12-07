#include "GameController.h"
#include "PlayerController.h"

using namespace gameEngine;

int main(int argc, char** argv)
{
	gc.createBG(100, "PNG/tiles/tile_01.png");
	gc.addCharacter(100, 50, "PNG/Man Brown/manBrown_stand.png", "Brown", 500, 500);
	pc.addPlayer(100, 10, "PNG/survivor 1/survivor1_gun.png", "player", 250, 250);
	pc.eventHandler();

	return 0;
}

