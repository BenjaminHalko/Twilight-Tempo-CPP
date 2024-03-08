#include "global.h"
#include "object.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Object::Object(float xstart, float ystart, std::string sprite_path, float sprite_xoffset, float sprite_yoffset) {
	x = xstart;
	y = ystart;
	sprite = Sprite(sprite_path);
	xscale = 1;
	yscale = 1;
	sprite_width = sprite.getWidth();
	sprite_height = sprite.getHeight();
	sprite().setOrigin(sprite_width*sprite_xoffset, sprite_height*sprite_yoffset);
}

void Object::update() {}

void Object::draw() {
	sf::Sprite &mySprite = sprite();
	mySprite.setPosition(x, y);
	mySprite.setScale(xscale, yscale);
	Global::window.draw(mySprite);
}