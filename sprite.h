#pragma once
#include <SFML/Graphics.hpp>
class Sprite {
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Sprite();
	Sprite(std::string filename);
	sf::Sprite& operator()();
	int getWidth();
	int getHeight();
};