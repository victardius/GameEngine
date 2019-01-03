#include "CollisionSprite.h"
#include "GameController.h"
#include <algorithm>

namespace gameEngine {

	CollisionSprite::CollisionSprite(std::shared_ptr<Animator> animat, std::string spriteName, int posX, int posY) : Sprite(animat, spriteName, posX, posY)
	{
		createColliders();
	}

	void CollisionSprite::tick() {
		tickFunction();
		updateCollRects();
		rdrCpy();
	}

	void CollisionSprite::updateCollRects() {
		for (int i = 0; i < getAnimation()->getFrames(); i++) {
			for (auto& r : colliders.at(getAnimation()->getActiveRect(i))) {
				r->x = getRect()->x + colliderPos.at(r)->x;
				r->y = getRect()->y + colliderPos.at(r)->y;
			}
		}
	}

	void CollisionSprite::createColliders() {
		colliders.clear();

		for (int i = 0; i < getAnimation()->getFrames(); i++) {
			const int width = (&getAnimation()->getRect()[i])->w;
			const int height = (&getAnimation()->getRect()[i])->h;
			std::vector<std::shared_ptr<SDL_Rect>> v;
			colliders.emplace((&getAnimation()->getRect()[i]), v);
			for (int h = 0; h < height; h++) {
				int x = 0, y = 0, wi = 0;
				bool coll = false;
				for (int w = 0; w < width; w++) {
					if (isOpaque(w + (&getAnimation()->getRect()[i])->x, h + (&getAnimation()->getRect()[i])->y)) {
						if (coll) {
							wi++;
						}
						else {
							coll = true;
							x = w + getRect()->x;
							y = h + getRect()->y;
							wi = 1;
						}
					}
					else if (coll) {
						coll = false;
						std::shared_ptr<SDL_Rect> r = std::shared_ptr<SDL_Rect>(new SDL_Rect{ x,y,wi,1 });
						colliders.at((&getAnimation()->getRect()[i])).push_back(r);
						colliderPos.emplace(r, std::shared_ptr<SDL_Point>(new SDL_Point{ x - getRect()->x, h }));
					}
				}
			}
		}
	}

	void CollisionSprite::checkCollision(std::shared_ptr<CollisionSprite> cs) {
		SDL_Rect* r = intersectRects(cs);
		if (r != nullptr) {
			for (int y = 0; y < r->h; y++) {
				for (int x = 0; x < r->w; x++) {
					int posX = r->x + x;
					int posY = r->y + y;
					SDL_Point p1 = { posX, posY };
					if (pointInCollider(&p1) && cs->pointInCollider(&p1))
						collisionEvent();
				}
			}
		}
	}

	bool CollisionSprite::pointInCollider(SDL_Point* p) {
		for (auto& r1 : colliders.at(getAnimation()->getActiveRect(getCurrentFrame()))) {
			if (SDL_PointInRect(p, r1.get())) {
				return true;
			}
		}
		return false;
	}

	bool CollisionSprite::isOpaque(int x, int y) {
		SDL_Surface* sf = getAnimation()->getSurf();
		SDL_LockSurface(sf);
		int bytes = sf->format->BytesPerPixel;
		char* p = (char*)sf->pixels + y * sf->pitch + x * bytes;
		Uint32 pixel;
		switch (bytes)
		{
			case 1:
				pixel = *p; 
				break;
			case 2:
				pixel = *(Uint16*)p;
				break;
			case 3:
				if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
					pixel = p[0] << 16 | p[1] << 8 | p[2];
				else
					pixel = p[0] | p[1] << 8 | p[2] << 16;
				break;
			case 4:
				pixel = *(Uint32*)p;
				break;
		}
		SDL_UnlockSurface(sf);
		Uint8 red, green, blue, alpha;
		SDL_GetRGBA(pixel, sf->format, &red, &green, &blue, &alpha);
		return alpha > 225;
	}

	SDL_Rect* CollisionSprite::intersectRects(std::shared_ptr<CollisionSprite> cs) {
		int xLeft = std::max(cs->getRect()->x, getRect()->x);
		int yTop = std::max(cs->getRect()->y, getRect()->y);
		int xRight = std::min(cs->getRect()->x + cs->getRect()->w, getRect()->x + getRect()->w);
		int yBottom = std::min(cs->getRect()->y + cs->getRect()->h, getRect()->y + getRect()->h);
		int width = xRight - xLeft;
		int height = yBottom - yTop;
		if (width > 0 && height > 0) {
			collRect = { xLeft, yTop, width, height };
			return &collRect;
		}

		return nullptr;
	}

	void CollisionSprite::setAnimation(std::shared_ptr<Animator> anim) {
		Sprite::setAnimation(anim);
		createColliders();
	}

	CollisionSprite::~CollisionSprite() {
		colliders.clear();
		colliderPos.clear();
	}
}