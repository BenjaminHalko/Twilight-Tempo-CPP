#pragma once
#include "global.h"
#include "helper.h"
#include <SFML/Graphics.hpp>
struct Star {
	float x = random_range(0, Global::RESW);
	float y = random_range(0, Global::RESH);
	sf::Color color = (irandom(2)) ? hexColor(0xd2de8e) : hexColor(0x60205a);
	float alpha1 = 0;
	float alpha2 = 0;
	float alphaSpd = 0;
	float alphaOffset = 0;
	float far = 0;
};
class StarGenerator {
private:
	static std::vector<std::shared_ptr<Star>> frontStars;
	static std::vector<std::shared_ptr<Star>> backStars;
public:
	static void init();
	static void update();
	static void drawStarsBack(float alpha);
	static void drawStarsFront(float alpha);
};
