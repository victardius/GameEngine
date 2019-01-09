#ifndef FYSICS_H
#define FYSICS_H

#include <SDL.h>

namespace gameEngine {

	class Fysics
	{
	public:
		void setHorizontalDrag(int amount);
		int getHorizontalDrag();
		void setVerticalDrag(int amount);
		int getVerticalDrag();
		void setBouncyness(int b);
		int getBouncyness();
		void movePos(int xPos, int yPos);
		void bounce(SDL_Point* p);
		SDL_Point* getPosition();
		~Fysics();
	protected:
		Fysics(int x, int y, int horizDrag, int vertDrag, int bounce);
		void updatePosition(SDL_Rect* r);
		void bouncing();
	private:
		int verticalDrag, horizontalDrag;
		int bouncyness, currBounce;
		SDL_Point position;
		SDL_Point direction;
	};

}

#endif