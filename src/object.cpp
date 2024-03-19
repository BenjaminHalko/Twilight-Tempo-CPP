#include "object.h"
#include <SFML/Graphics.hpp>

Object::Object(float xstart, float ystart, std::string sprite_path, float sprite_xoffset, float sprite_yoffset) {
	destroyed = false;
	x = xstart;
	y = ystart;
	xscale = 1;
	yscale = 1;
	if (!sprite_path.empty()) {
		sprite = Sprite(sprite_path, sprite_xoffset, sprite_yoffset);
		sprite_width = sprite.getWidth();
		sprite_height = sprite.getHeight();
	}
	else {
		sprite_width = 0;
		sprite_height = 0;
	}
}

void Object::update() {}

void Object::draw() {}

bool Object::isDestroyed() const {
	return destroyed;
}

bool Object::isColliding(Object& other) {
	return (x - sprite_width / 2.0f < other.x + other.sprite_width / 2.0f &&
				x + sprite_width / 2.0f > other.x - other.sprite_width / 2.0f &&
				y - sprite_height / 2.0f < other.y + other.sprite_height / 2.0f &&
				y + sprite_height / 2.0f > other.y - other.sprite_height / 2.0f);
}
