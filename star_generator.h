#pragma once
#include <SFML/Graphics.hpp>
struct Star {
	int x = 0;
	int y = 0;
	sf::Color color = sf::Color::White;
	float alpha1 = 0;
	float alpha2 = 0;
	float alphaSpd = 0;
	float alphaOffset = 0;
};
class StarGenerator {
private:
	static std::vector<Star*> frontStars;
	static std::vector<Star*> backStars;
public:
	static void init();
	static void update();
	static void drawStarsBack(float alpha);
	static void drawStarsFront(float alpha);
	static void deleteStars();
};