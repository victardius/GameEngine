#ifndef COLLISIONSPRITE_H
#define COLLISIONSPRITE_H

#include "Sprite.h"
#include <vector>

namespace gameEngine {

	class CollisionSprite : public Sprite
	{
	public:
		static CollisionSprite* getInstance(const char* path, std::string spriteName, int posX = 0, int posY = 0, int sizeW = 0, int sizeH = 0);
		void checkCollision(CollisionSprite* cs);
	protected:
		CollisionSprite(const char* path, std::string spriteName, int posX = 0, int posY = 0, int sizeW = 0, int sizeH = 0);
	private:
		bool isOpaque(int x, int y);
		SDL_Rect* intersectRects(CollisionSprite* cs);
		SDL_Rect collRect;
		bool collided = false;
	};

}

#endif

