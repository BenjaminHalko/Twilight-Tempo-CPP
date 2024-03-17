#pragma once
#include <SFML/Graphics.hpp>
class Sprite {
private:
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Sprite();
	Sprite(std::string filename, const float xorigin=0, const float yorigin=0);
	sf::Sprite& operator()();
	int getWidth();
	int getHeight();
};
