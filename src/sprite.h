#pragma once
#include <SFML/Graphics.hpp>
class Sprite {
private:
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Sprite();
	explicit Sprite(const std::string& filename, float xorigin=0, float yorigin=0);
	sf::Sprite& operator()();
	int getWidth();
	int getHeight();
};
