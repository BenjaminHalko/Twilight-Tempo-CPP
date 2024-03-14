#pragma once
#include "object.h"
class ScorePopup : public Object {
	std::string points;
	float alpha;
public:
	ScorePopup(float x, float y, int points);
	void update();
	void draw();
};