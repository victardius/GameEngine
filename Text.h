#ifndef TEXT_H
#define TEXT_H

#include "Sprite.h"
#include <SDL_ttf.h>
#include <memory>

namespace gameEngine {

	class Text : public Sprite
	{
	public:
		static std::shared_ptr<Text> getInstance(std::shared_ptr<Animator> animat, std::string spriteName, std::string txt, const char* fontPath, SDL_Color* c, int size, int posX = 0, int posY = 0);
		void tick();
		void setText(std::string s);
		std::string getText();
		virtual bool isActive();
		virtual void setActive();
		~Text();
	protected:
		Text(std::shared_ptr<Animator> animat, std::string spriteName, std::string txt, const char* fontPath, SDL_Color* c, int size, int posX, int posY);
		virtual void tickFunction();
	private:
		TTF_Font* font;
		std::string text;
		SDL_Surface* txtSurf;
		SDL_Texture* txtTx;
		SDL_Color* color;
		void createText();
		void renderText();
		bool active = false;
	};

}

#endif

