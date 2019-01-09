#include "Fysics.h"
#include "GameController.h"

namespace gameEngine {

	Fysics::Fysics(int x, int y, int horizDrag, int vertDrag, int bounce) : horizontalDrag(horizDrag), verticalDrag(vertDrag), bouncyness(bounce)
	{
		position = { x, y };
	}

	void Fysics::setVerticalDrag(int amount) {
		verticalDrag = amount;
	}

	int Fysics::getVerticalDrag() {
		return verticalDrag;
	}

	void Fysics::setHorizontalDrag(int amount) {
		horizontalDrag = amount;
	}

	int Fysics::getHorizontalDrag() {
		return horizontalDrag;
	}

	void Fysics::setBouncyness(int b) {
		bouncyness = b;
	}

	int Fysics::getBouncyness() {
		return bouncyness;
	}

	void Fysics::movePos(int xPos, int yPos) {
		position.x += xPos + verticalDrag / gc.getFPS();
		position.y += yPos + horizontalDrag / gc.getFPS();
	}

	void Fysics::bounce(SDL_Point* p) {
		currBounce = bouncyness;
		if (position.x - p->x > 0)
			direction.x = 1;
		else if (position.x - p->x < 0)
			direction.x = -1;
		else
			direction.x = 0;

		if (position.y - p->y > 0)
			direction.y = 1;
		else if (position.y - p->y < 0)
			direction.y = -1;
		else
			direction.y = 0;
	}

	void Fysics::bouncing() {
		if (currBounce) {
			movePos(direction.x, direction.y);
			currBounce--;
		}
	}

	void Fysics::updatePosition(SDL_Rect* r) {
		movePos(0, 0);
		r->x = position.x;
		r->y = position.y;
	}

	SDL_Point* Fysics::getPosition() {
		return &position;
	}

	Fysics::~Fysics()
	{
	}

}