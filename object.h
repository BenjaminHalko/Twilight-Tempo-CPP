#pragma once
#include "sprite.h"
#include <SFML/Graphics.hpp>
class Object {
protected:
	float x;
	float y;
	Sprite sprite;
	float xscale;
	float yscale;
	int sprite_width;
	int sprite_height;
	bool destroyed;
public:
	Object(float xstart, float ystart, std::string sprite_path="", float sprite_xoffset = 0.5, float sprite_yoffset = 0.5);
	virtual void update();
	virtual void draw();
	bool isDestroyed() const;
	bool isColliding(Object& other);
};
