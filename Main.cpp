#include "GameController.h"


int main(int argc, char** argv)
{
	GameController*  gc = new GameController();

	gc->createBG(100, "PNG/tiles/tile_01.png");
	gc->addPlayer(100, 5.5, "PNG/survivor 1/survivor1_gun.png", "player", 250, 250);
	gc->eventHandler();

	return 0;
}

