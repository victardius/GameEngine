#ifndef COLLISIONSPRITE_H
#define COLLISIONSPRITE_H

#include "Sprite.h"
#include "Animator.h"
#include <vector>
#include <unordered_map>

namespace gameEngine {

	class CollisionSprite : public Sprite
	{
	public:
		void checkCollision(CollisionSprite* cs);
		std::unordered_map<SDL_Rect*, std::vector<SDL_Rect*>> getColliders() { return colliders; }
		void createColliders();
		void setAnimation(Animator* anim);
	protected:
		CollisionSprite(Animator* animat, std::string spriteName, int posX = 0, int posY = 0);
		virtual void collisionEvent() = 0; //måste överskuggas i en spelimplemmentering
		bool collided = false;
	private:
		bool isOpaque(int x, int y);
		SDL_Rect* intersectRects(CollisionSprite* cs);
		SDL_Rect collRect;
		//std::vector<SDL_Rect*> colliders;
		std::unordered_map<SDL_Rect*, std::vector<SDL_Rect*>> colliders;
	};

}

#endif

