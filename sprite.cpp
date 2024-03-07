#include "sprite.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Sprite::Sprite() {}

Sprite::Sprite(const std::string filename) {
	texture.loadFromFile("sprites/"+filename);
}

sf::Sprite Sprite::operator()() {
	sprite.setTexture(texture);
	return sprite;
}
