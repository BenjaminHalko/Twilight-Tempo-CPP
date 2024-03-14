#pragma once
#include "object.h"
class Enemy : public Object {
private:
	float direction;
	bool dead;
	float deadPercent;
	bool hit;
	float circlePercent;
	float speed;
	float timePoints;
	bool flash;
	Sprite flashSprite;
	Sprite cornerSprite;
	float angle;
	float alpha;
public:
	Enemy(float xPos, float yPos, float dir);
	void update();
	void draw();
	void killEnemy(int amountOfPoints);
	bool isDead() const;
	float getDirection() const;
};