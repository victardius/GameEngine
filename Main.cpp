#include "GameController.h"

using namespace gameEngine;



void movePlayer() {
	gc.getPlayer()->moveTarget();
}

void shootPlayer() {
	gc.getPlayer()->shoot();
}

void quit() {
	gc.quit();
}

int main(int argc, char** argv)
{
	gc.createBG(100, "PNG/tiles/tile_01.png");
	gc.addCharacter(100, 50, "PNG/Man Brown/manBrown_stand.png", "Brown", 500, 500);
	gc.setPlayer(gc.addCharacter(100, 5, "PNG/survivor 1/survivor1_gun.png", "player", 250, 250));
	gc.getPlayer()->setAnimation(Animator::getInstance("PNG/survivor 1/survivor1_gun_sheet.png", 52, 52, 8));
	gc.getPlayer()->getAnimation()->setAngleBased(true);
	gc.SetRightMouseButton(movePlayer);
	gc.SetLeftMouseButton(shootPlayer);
	gc.SetEscapeKey(quit);
	gc.start();

	return 0;
}

