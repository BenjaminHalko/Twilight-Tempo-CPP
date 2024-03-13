#pragma once

#include <SFML/Graphics.hpp>

class GUI {
private:
	static sf::Font m3x6;
	static sf::Font pressStart;
public:
	static void init();
	static void draw();
	static void drawText(sf::Font font, std::string textString, int characterSize, int x, int y, bool horizCentered, bool vertCentered, sf::Color = sf::Color::White);
};