#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "sprite.h"

class GUI {
private:
	static sf::Font m3x6;
	static sf::Font pressStart;
	static std::vector<Sprite*> hearts;
public:
	static void init();
	static void draw();
};