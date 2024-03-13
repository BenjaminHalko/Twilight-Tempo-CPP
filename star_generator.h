#pragma once
#include <SFML/Graphics.hpp>
struct Star {
	float x;
	float y;
	sf::Color color;
	float alpha1;
	float alpha2;
	float alphaSpd;
	float alphaOffset;
};
class StarGenerator {
private:
	static std::vector<Star*> frontStars;
	static std::vector<Star*> backStars;
public:
	static void init();
	static void update();
	static void drawStarsBack(float alpha);
	static void drawStarsFront();
};