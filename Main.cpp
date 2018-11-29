#include "GameController.h"


int main(int argc, char * argv[])
{
	GameController*  gc = new GameController();

	gc->init();
	gc->addBackground("PNG/bilden.png", "background");
	gc->addPlayer(100, 5.5, "PNG/survivor 1/survivor1_gun.png", "player", 250, 250);
	gc->eventHandler();
	gc->end();

	return 0;
}