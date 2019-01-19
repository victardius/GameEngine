#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <memory>
#include "CollisionSprite.h"
#include "Background.h"
#include "Text.h"

namespace gameEngine {

	class Level
	{
	public:
		static std::shared_ptr<Level> getInstance();
		void addBackground(std::shared_ptr<Background> bg);
		void addCollisionSprite(std::shared_ptr<CollisionSprite> character);
		void addText(std::shared_ptr<Text> text);
		const std::vector<std::shared_ptr<CollisionSprite>>* getCollidingObjects();
		const std::vector<std::shared_ptr<Background>>* getBackgrounds();
		const std::vector<std::shared_ptr<Text>>* getTexts();
		void removeCollidingObject(std::shared_ptr<CollisionSprite> n);
		void removeBackground(std::shared_ptr<Background> n);
		void removeText(std::shared_ptr<Text> n);
		void removeObjects();
		~Level();
	protected:
		Level();
	private:
		std::vector<std::shared_ptr<CollisionSprite>> collObjs;
		std::vector<std::shared_ptr<Background>> bgs;
		std::vector<std::shared_ptr<Text>> texts;
		std::vector<std::shared_ptr<CollisionSprite>> removeCollObjs;
		std::vector<std::shared_ptr<Background>> removeBgs;
		std::vector<std::shared_ptr<Text>> removeTexts;
	};

}

#endif