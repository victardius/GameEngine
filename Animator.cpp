#include "Animator.h"
#include "GameController.h"

namespace gameEngine {

	Animator::Animator(const char* sheetPath, int w, int h, int frames)
	{
		sf = IMG_Load(sheetPath);
		tx = SDL_CreateTextureFromSurface(gc.getSys()->getRen(), sf);
		rect = new SDL_Rect[frames];
		SDL_QueryTexture(tx, NULL, NULL, &totSizeW, &totSizeH);
		int x = 0, y = 0;
		for (int i = 0; i < frames; i++) {
			if ((y == 0 && w * i > totSizeW) || (y > 0 && w * i > totSizeW * y))
				y++;
			x = (w * i) - (totSizeW * y);
			rect[i] = {x, y * h, w, h};
		}
	}

	Animator* Animator::getInstance(const char* sheetPath, int w, int h, int frames) {
		return new Animator(sheetPath, w, h, frames);
	}

	Animator::~Animator()
	{
	}

}