#include "CollisionSprite.h"
#include "GameController.h"
#include <algorithm>

namespace gameEngine {

	CollisionSprite::CollisionSprite(const char* path, std::string spriteName, int posX, int posY, int sizeW, int sizeH) : Sprite(path, spriteName, posX, posY, sizeW, sizeH)
	{
		createColliders();
	}

	void CollisionSprite::createColliders() {
		colliders.clear();
		std::vector<SDL_Rect*> r;
		if (getAnimation() == nullptr)
			r.push_back(getRect());
		else {
			for (int i = 0; i < getAnimation()->getFrames(); i++)
			r.push_back(&getAnimation()->getRect()[i]);
		}
		int count = 0;

		for (SDL_Rect* re : r) {
			const int width = re->w;
			const int height = re->h;
			std::vector<SDL_Rect*> v;
			colliders.emplace(re, v);
			for (int h = 0; h < height; h++) {
				int x = 0, y = 0, wi = 0;
				bool coll = false;
				for (int w = 0; w < width; w++) {
					if (isOpaque(w, h)) {
						if (coll) {
							wi++;
						}
						else {
							coll = true;
							x = w + re->x;
							y = h + re->y;
							wi = 1;
						}
					}
					else if (coll) {
						coll = false;
						SDL_Rect* rect = new SDL_Rect{ x,y,wi,1 };
						colliders.at(re).push_back(rect);
						count++;
					}
				}
			}
		}
		std::cerr << count << std::endl;
		std::cerr << colliders.at(getActiveRect()).size() << "   " << std::endl;
	}

	void CollisionSprite::checkCollision(CollisionSprite* cs) {
		SDL_Rect* r = intersectRects(cs);
		if (r != nullptr) {
			for (int y = 0; y < r->h; y++) {
				for (int x = 0; x < r->w; x++) {
					int posX = r->x + x;
					int posY = r->y + y;
					SDL_Point p1 = { posX, posY };
					for (SDL_Rect* r1 : colliders.at(getActiveRect())) {
						if (SDL_PointInRect(&p1, r1)) {
							for (SDL_Rect* r2 : cs->getColliders().at(cs->getActiveRect())) {
								if (SDL_PointInRect(&p1, r2)) {
									collisionEvent();
								}
							}
						}
					}
				}
			}
		}
	}

	bool CollisionSprite::isOpaque(int x, int y) {
		SDL_Surface* sf;
		if (getAnimation() == nullptr)
			sf = getSurface();
		else {
			sf = getAnimation()->getSurf();
		}
		SDL_LockSurface(sf);
		int bytes = sf->format->BytesPerPixel;
		char* p = (char*)sf->pixels + y * getSurface()->pitch + x * bytes;
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

	SDL_Rect* CollisionSprite::intersectRects(CollisionSprite* cs) {
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

	void CollisionSprite::setAnimation(Animator* anim) {
		Sprite::setAnimation(anim);
		createColliders();
	}

}