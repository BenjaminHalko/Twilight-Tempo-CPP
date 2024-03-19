#include "sprite.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Sprite::Sprite() = default;

// Load in texture from the file name
Sprite::Sprite(std::string filename, float xorigin, float yorigin) {
	texture.loadFromFile("resources/sprites/"+filename);
	sprite.setOrigin(std::round(xorigin * (float)getWidth()), std::round(yorigin * (float)getHeight()));
}

// Load sprite from a texture
sf::Sprite& Sprite::operator()() {
	sprite.setTexture(texture);
	return sprite;
}

int Sprite::getWidth() {
	return texture.getSize().x;
}

int Sprite::getHeight() {
	return texture.getSize().y;
}
