#pragma once
#include "object.h"
#include "after_image.h"
#include <vector>
class Bullet : public Object {
private:
	float direction;
	float spd;
	bool dead = false;
	std::vector<AfterImage> image;
	int time;
	int startdir;
	int length;
	float lastX;
	float lastY;
	float waveX;
	float waveY;
	float amountOfPoints;
public:
	Bullet(float xPos, float yPos, float dir);
	void update();
	void draw();
};
