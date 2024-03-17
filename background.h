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
	static bool isNight;
	static int timer;
public:
	static void init();
	static void setNight(bool night);
	static void update();
	static void draw();
};
