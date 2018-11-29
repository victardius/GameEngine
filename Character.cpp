#include "Character.h"

int Character::move(SDL_Rect* b) {

	int distX;
	int distY;
	
	distX = (b->x + (b->w / 2) - (this->getRect()->w / 2)) - getRect()->x;
	distY = (b->y + (b->h / 2) - (this->getRect()->h / 2)) - getRect()->y;

	if (distX > 0) {
		getRect()->x++;
	}else if(distX < 0){
		getRect()->x--;
	}

	if (distY > 0) {
		getRect()->y++;
	}
	else if (distY < 0) {
		getRect()->y--;
	}
	std::cout << "Me: " << getRect()->x << " : " << getRect()->y << std::endl;
	std::cout << "Distance: " << distX << " : " << distY << std::endl;
	std::cout << "Target: " << b->x + (b->w / 2) << " : " << b->y + (b->h / 2) << std::endl;

	return distX + distY;
	
}