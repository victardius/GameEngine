#ifndef COLLISIONSPRITE_H
#define COLLISIONSPRITE_H

#include "Sprite.h"
#include <vector>

namespace gameEngine {

	class CollisionSprite : public Sprite
	{
	public:
		void checkCollision(CollisionSprite* cs);
	protected:
		CollisionSprite(const char* path, std::string spriteName, int posX = 0, int posY = 0, int sizeW = 0, int sizeH = 0);
		virtual void collisionEvent() = 0; //måste överskuggas i en spelimplemmentering
	private:
		bool isOpaque(int x, int y);
		SDL_Rect* intersectRects(CollisionSprite* cs);
		SDL_Rect collRect;
		bool collided = false;
		void createColliders();
		std::vector<SDL_Rect*> colliders;
	};

}

#endif

