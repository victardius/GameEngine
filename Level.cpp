#include "Level.h"

namespace gameEngine {

	Level::Level()
	{
	}

	std::shared_ptr<Level> Level::getInstance() {
		return std::shared_ptr<Level>(new Level());
	}

	void Level::addBackground(std::shared_ptr<Background> bg) {
		bgs.push_back(bg);
	}

	void Level::addCollisionSprite(std::shared_ptr<CollisionSprite> character) {
		collObjs.push_back(character);
	}

	void Level::addText(std::shared_ptr<Text> text) {
		texts.push_back(text);
	}

	std::vector<std::shared_ptr<CollisionSprite>>* Level::getCollidingObjects() {
		return &collObjs;
	}

	std::vector<std::shared_ptr<Background>>* Level::getBackgrounds() {
		return &bgs;
	}

	std::vector<std::shared_ptr<Text>>* Level::getTexts() {
		return &texts;
	}

	void Level::removeCollidingObject(std::shared_ptr<CollisionSprite> n) {
		removeCollObjs.push_back(n);
	}

	void Level::removeBackground(std::shared_ptr<Background> n) {
		removeBgs.push_back(n);
	}

	void Level::removeText(std::shared_ptr<Text> n) {
		removeTexts.push_back(n);
	}

	void Level::removeObjects() {
		for (std::shared_ptr<CollisionSprite> cs : removeCollObjs) {
			for (std::vector<std::shared_ptr<CollisionSprite>>::iterator i = collObjs.begin(); i != collObjs.end(); )
				if (*i == cs) {
					i = collObjs.erase(i);
				}
				else
					i++;
		}
		removeCollObjs.clear();

		for (std::shared_ptr<Background> bg : removeBgs) {
			for (std::vector<std::shared_ptr<Background>>::iterator i = bgs.begin(); i != bgs.end(); )
				if (*i == bg) {
					i = bgs.erase(i);
				}
				else
					i++;
		}
		removeBgs.clear();

		for (std::shared_ptr<Text> txt : removeTexts) {
			for (std::vector<std::shared_ptr<Text>>::iterator i = texts.begin(); i != texts.end(); )
				if (*i == txt) {
					i = texts.erase(i);
				}
				else
					i++;
		}
		removeTexts.clear();
	}

	Level::~Level()
	{
		bgs.clear();
		collObjs.clear();
		texts.clear();
		removeCollObjs.clear();
		removeBgs.clear();
		removeTexts.clear();
	}

}