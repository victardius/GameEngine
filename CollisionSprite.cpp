#include "CollisionSprite.h"
#include "GameController.h"
#include <algorithm>

namespace gameEngine {

	CollisionSprite::CollisionSprite(const char* path, std::string spriteName, int posX, int posY, int sizeW, int sizeH) : Sprite(path, spriteName, posX, posY, sizeW, sizeH)
	{
	}

	void CollisionSprite::checkCollision(CollisionSprite* cs) {
		/*int rightX1 = getRect()->x + getRect()->w;
		int bottomY1 = getRect()->y + getRect()->h;
		int rightX2 = cs->getRect()->x + cs->getRect()->w;
		int bottomY2 = cs->getRect()->y + cs->getRect()->h;
		if ((cs->getRect()->x < rightX1 && cs->getRect()->y < bottomY1) && !(rightX2 < getRect()->x || bottomY2 < getRect()->y)) {*/
			SDL_Rect* r = intersectRects(cs);
			if (r != nullptr) {
				for (int y = 0; y < r->h; y++) {
					for (int x = 0; x < r->w; x++) {
						int posX = r->x + x;
						int posY = r->y + y;
						if (isOpaque(posX, posY)) {
							//std::cout << "First done" << std::endl;
							if (cs->isOpaque(posX, posY)) {
								collisionEvent();
							}
						}
					}
				}
			/*}*/
			//std::cout << "Not correct :S" << std::endl;
		}
	}

	bool CollisionSprite::isOpaque(int x, int y) {
		x -= getRect()->x;
		y -= getRect()->y;
		SDL_LockSurface(getSurface());
		int bytes = getSurface()->format->BytesPerPixel;
		char* p = (char*)getSurface()->pixels + y * getSurface()->pitch + x * bytes;
		Uint32 pixel;
		//std::cout << "Bytes: " << bytes << std::endl;
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
		SDL_UnlockSurface(getSurface());
		Uint8 red, green, blue, alpha;
		SDL_GetRGBA(pixel, getSurface()->format, &red, &green, &blue, &alpha);
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

	/*CollisionSprite* CollisionSprite::getInstance(const char* path, std::string spriteName, int posX, int posY, int sizeW, int sizeH) {
		return new CollisionSprite(path, spriteName, posX, posY, sizeW, sizeH);
	}*/

}