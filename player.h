#pragma once
#include "sprite.h"
#include "object.h"
#include "death_particle.h"
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

	float deathSpd;

	int penalty;

	float startScale;

	bool dead;

	std::vector<std::shared_ptr<DeathParticle>> deathParticles;
public:
	Player(float xPos, float yPos);
	void update();
	void draw();

	void setCannonMove(float val);
	void applyShake(int dir);
};