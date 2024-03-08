#pragma once
#include <SFML/Graphics.hpp>
#include "sprite.h"
class Background {
private:
	static Sprite backgroundSprite[4];
	static Sprite cloudSprite;
	static sf::Color backgroundColors[4];
	static sf::Color cloudColors[5];
	static int backgroundIndex;
	static sf::Texture texture;
	static sf::Sprite sprite;
public:
	Background();
	static void updateBG(int index);
	static void draw();
};