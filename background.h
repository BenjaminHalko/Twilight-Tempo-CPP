#pragma once
#include <SFML/Graphics.hpp>
#include "sprite.h"
class Background {
private:
	Sprite backgroundSprite[4];
	Sprite cloudSprite;
	sf::Color backgroundColors[4];
	sf::Color cloudColors[5];
	int backgroundIndex;
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Background();
	void updateBG(int index);
	void draw(sf::RenderWindow &window);
};