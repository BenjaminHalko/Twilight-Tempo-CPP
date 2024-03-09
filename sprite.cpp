#include "sprite.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Sprite::Sprite() {}

// Load in texture from the file name
Sprite::Sprite(const std::string filename) {
	texture.loadFromFile("sprites/"+filename);
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
