#include <cmath>
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
		this->frames = frames;
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

	void Animator::renderFrame(int frame, SDL_Rect* dest) {
		if (!angleBased)
			SDL_RenderCopy(gc.getSys()->getRen(), tx, &rect[frame], dest);
		else {
			double a = 360 / frames;
			a = frame / a;
			a = round(a) - 1;
			int b = a;
			SDL_RenderCopy(gc.getSys()->getRen(), tx, &rect[b], dest);
		}
	}

	void Animator::setAngleBased(bool b) {
		angleBased = b;
	}

	bool Animator::isAngleBased() {
		return angleBased;
	}

	Animator::~Animator()
	{
	}

}