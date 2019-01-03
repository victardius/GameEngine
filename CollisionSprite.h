#ifndef COLLISIONSPRITE_H
#define COLLISIONSPRITE_H

#include "Sprite.h"
#include "Animator.h"
#include "Coordinate.h"
#include <vector>
#include <unordered_map>
#include <memory>

namespace gameEngine {

	class CollisionSprite : public Sprite
	{
	public:
		void checkCollision(std::shared_ptr<CollisionSprite> cs);
		void createColliders();
		void setAnimation(std::shared_ptr<Animator> anim);
		void tick();
		std::unordered_map<SDL_Rect*, std::vector<std::shared_ptr<SDL_Rect>>> getColliders() { return colliders; }
		~CollisionSprite();
	protected:
		CollisionSprite(std::shared_ptr<Animator> animat, std::string spriteName, int posX = 0, int posY = 0);
		virtual void collisionEvent() = 0;
		virtual void tickFunction() = 0;
	private:
		bool isOpaque(int x, int y);
		SDL_Rect* intersectRects(std::shared_ptr<CollisionSprite> cs);
		SDL_Rect collRect;
		std::unordered_map<SDL_Rect*, std::vector<std::shared_ptr<SDL_Rect>>> colliders;
		std::unordered_map<std::shared_ptr<SDL_Rect>, std::shared_ptr<SDL_Point>> colliderPos;
		bool collided = false;
		void updateCollRects();
		bool pointInCollider(SDL_Point* p);
	};

}

#endif

