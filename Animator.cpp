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
		int x = 0, y = 0;
		this->frames = frames;
		for (int i = 0; i < frames; i++) {
			if ((y == 0 && w * i >= totSizeW) || (y > 0 && w * i > totSizeW * (y + 1)))
				y++;
			x = (w * i) - (totSizeW * y);
			rect[i] = {x, (y * h), w, h};
		}
	}

	Animator* Animator::getInstance(const char* sheetPath, int w, int h, int frames) {
		return new Animator(sheetPath, w, h, frames);
	}

	/*void Animator::renderFrame(int frame, SDL_Rect* dest) {
		if (!angleBased)
			SDL_RenderCopy(gc.getSys()->getRen(), tx, &rect[frame], dest);
		else {
			if (frame < 0)
				frame += 360;
			double a = 360 / frames;
			a = frame / a;
			a = round(a);
			currentFrame = a;
			if (currentFrame == frames)
				currentFrame = 0;
			SDL_RenderCopy(gc.getSys()->getRen(), tx, &rect[currentFrame], dest);
		}
	}*/

	SDL_Rect* Animator::getRect() {
		return rect;
	}

	SDL_Rect* Animator::getActiveRect(int frame) {
		if (frame > (frames -1) || frame < 0)
			throw std::out_of_range("Loading sprite frame is out of bounds!");
		return &rect[frame];
	}

	SDL_Surface* Animator::getSurf() {
		return sf;
	}

	int Animator::getXDiff() {
		return rect->x - getRect()->x;
	}

	int Animator::getYDiff() {
		return rect->y - getRect()->y;
	}

	int Animator::getFrames() {
		return frames;
	}

	SDL_Texture* Animator::getTx() {
		return tx;
	}

	Animator::~Animator()
	{
	}

}