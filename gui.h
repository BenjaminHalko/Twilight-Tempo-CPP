#pragma once

#include <SFML/Graphics.hpp>

class GUI {
private:
	static sf::Font m3x6;
	static sf::Font pressStart;
public:
	static void init();
	static void draw();
};