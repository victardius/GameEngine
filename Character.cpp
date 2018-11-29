#include "Character.h"


void Character::move(Background* b) {
	int distX = 0;
	int distY = 0;
	int x = Sprite::getX();
	int y = Sprite::getY();
	
	do {
		int distX = b->Sprite::getX() - x;
		int distY = b->Sprite::getY() - y;

		if (distX > 0) {
			x++;
		}else if(distX < 0){
			x--;
		}

		if (distY > 0) {
			y++;
		}
		else if (distY < 0) {
			y--;
		}
		Sprite::moveTo(distX, distY);
	}while (distX + distY != 0);
	
}