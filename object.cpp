#include "global.h"
#include "object.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Object::Object(float xstart, float ystart, std::string sprite_path, float sprite_xoffset, float sprite_yoffset) {
	destroyed = false;
	x = xstart;
	y = ystart;
	sprite = Sprite(sprite_path, sprite_xoffset, sprite_yoffset);
	xscale = 1;
	yscale = 1;
	sprite_width = sprite.getWidth();
	sprite_height = sprite.getHeight();
}

void Object::update() {}

void Object::draw() {
	sf::Sprite &mySprite = sprite();
	mySprite.setPosition(x, y);
	mySprite.setScale(xscale, yscale);
	Global::render.draw(mySprite);
}

bool Object::isDestroyed() {
	return destroyed;
}

bool Object::isColliding(Object& other) {
	return (x - sprite_width / 2 < other.x + other.sprite_width / 2 &&
				x + sprite_width / 2 > other.x - other.sprite_width / 2 &&
				y - sprite_height / 2 < other.y + other.sprite_height / 2 &&
				y + sprite_height / 2 > other.y - other.sprite_height / 2);
}