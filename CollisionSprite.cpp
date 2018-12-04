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
								std::cout << "collision!" << std::endl;
								collided = true;
							}
						}
					}
				}
			/*}*/
			//std::cout << "Not correct :S" << std::endl;
		}
	}

	bool CollisionSprite::isOpaque(int x, int y) {
		SDL_LockSurface(getSurface());
		int bytes = getSurface()->format->BytesPerPixel;
		Uint8* pixel = ((Uint8*)getSurface()->pixels + y * getSurface()->pitch + x * bytes);
		Uint32 pixelColor;
		//std::cout << "Bytes: " << bytes << std::endl;
		switch (bytes)
		{
			case(1):
				pixelColor = *((Uint8*)getSurface()->pixels + y * getSurface()->pitch + x * bytes);
				break;
			case(2):
				pixelColor = *(Uint16*)((Uint8*)getSurface()->pixels + y * getSurface()->pitch + x * bytes);
				break;
			case(4):
				pixelColor = (Uint32)((Uint8*)getSurface()->pixels + y * getSurface()->pitch + x * bytes);
				break;
		}
		Uint8 red, green, blue, alpha;
		SDL_GetRGBA(pixelColor, getSurface()->format, &red, &green, &blue, &alpha);
		int a = alpha;
		if (a > 100)
			std::cout << a << std::endl;
		SDL_UnlockSurface(getSurface());
		return alpha > 100;
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

	CollisionSprite* CollisionSprite::getInstance(const char* path, std::string spriteName, int posX, int posY, int sizeW, int sizeH) {
		return new CollisionSprite(path, spriteName, posX, posY, sizeW, sizeH);
	}

}