#pragma once
#include "sprite.h"
#include "object.h"
#include "bezier.h"
class Player : public Object {
private:
	Sprite cannonSprite;

	int dir;
	float dirDraw;
	int lastDir;

	float shootPercent;
	static const int cannonLength = 10;
	static const int bulletLength = 11;

	float shake[4];
	float generalShake;

	float cannonMove;

	static const int deathSpd = 45;

	float penalty;

	float startScale = 0;

	bezier::Bezier<3> cubicBezier;
public:
	Player(float xPos, float yPos);
	void update();
	void draw();

	void setCannonMove(float val);
};