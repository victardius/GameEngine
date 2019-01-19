#include "Text.h"
#include "GameController.h"

namespace gameEngine {

	Text::Text(std::shared_ptr<Animator> animat, std::string spriteName, std::string txt, const char* fontPath, SDL_Color* c, int size, int posX, int posY) : Sprite(animat, spriteName, posX, posY), text(txt), color(c)
	{
		font = TTF_OpenFont(fontPath, size);
		if (font == nullptr)
			throw std::runtime_error("Font not found!");
		createText();
	}

	std::shared_ptr<Text> Text::getInstance(std::shared_ptr<Animator> animat, std::string spriteName, std::string txt, const char* fontPath, SDL_Color* c, int size, int posX, int posY) {
		return std::shared_ptr<Text>(new Text(animat, spriteName, txt, fontPath, c, size, posX, posY));
	}

	void Text::tick() {
		tickFunction();
		rdrCpy();
		renderText();
	}

	void Text::tickFunction() {

	}

	void Text::createText() {
		if (text == "")
			text = " ";
		txtSurf = TTF_RenderText_Solid(font, text.c_str(), *color);
		txtTx = SDL_CreateTextureFromSurface(gc.getSys()->getRen(), txtSurf);
		getRect()->w = txtSurf->w;
		getRect()->h = txtSurf->h;
		
	}

	void Text::renderText() {
		SDL_RenderCopy(gc.getSys()->getRen(), txtTx, NULL, getRect());
	}

	void Text::setText(std::string s) {
		text = s;
		createText();
	}

	std::string Text::getText() const {
		return text;
	}

	bool Text::isActive() {
		return active;
	}
	
	void Text::setActive() {
		active = !active;
		gc.setTyping(active);
	}

	Text::~Text() {
		SDL_DestroyTexture(txtTx);
		SDL_FreeSurface(txtSurf);
		TTF_CloseFont(font);
		delete color;
	}

}