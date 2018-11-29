#include "GameController.h"


int main(int argc, char * argv[])
{
	GameController*  gc = new GameController();
	//std:unique_ptr<GameController> gc(new GameController());

	gc->init();
	gc->addTexture("PNG/bilden.png", "background");
	gc->addTexture("PNG/survivor 1/survivor1_gun.png", "player", 250, 250);
	gc->eventHandler();
	gc->end();

	return 0;
}