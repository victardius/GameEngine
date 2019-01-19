#include <cmath>
#include <stdexcept>
#include "Animator.h"
#include "GameController.h"

namespace gameEngine {

	Animator::Animator(const char* sheetPath, int w, int h, int frames)
	{
		sf = IMG_Load(sheetPath);
		tx = SDL_CreateTextureFromSurface(gc.getSys()->getRen(), sf);
		rect = new SDL_Rect[frames];
		SDL_QueryTexture(tx, NULL, NULL, &totSizeW, &totSizeH);
		if (w == 0 && h == 0) {
			w = totSizeW;
			h = totSizeH;
		}
		int x = 0, y = 0;
		this->frames = frames;
		for (int i = 0; i < frames; i++) {
			if (y >= 0 && w * (i + 1) > totSizeW * (y + 1) && frames > 1)
				y++;
			x = (w * i) - (totSizeW * y);
			rect[i] = {x, (y * h), w, h};
		}
	}

	std::shared_ptr<Animator> Animator::getInstance(const char* sheetPath, int w, int h, int frames) {
		return std::shared_ptr<Animator>(new Animator(sheetPath, w, h, frames));
	}

	const SDL_Rect* Animator::getRect() {
		return rect;
	}

	const SDL_Rect* Animator::getActiveRect(int frame) {
		if (frame > (frames -1) || frame < 0)
			throw std::out_of_range("Loading sprite frame is out of bounds!");
		return &rect[frame];
	}

	SDL_Surface* Animator::getSurf() {
		return sf;
	}

	int Animator::getFrames() const {
		return frames;
	}

	SDL_Texture* Animator::getTx() {
		return tx;
	}

	Animator::~Animator()
	{
		SDL_FreeSurface(sf);
		SDL_DestroyTexture(tx);
		delete rect;
	}

}