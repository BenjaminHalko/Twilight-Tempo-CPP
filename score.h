#pragma once
#include "object.h"
class Score : public Object {
	std::string points;
public:
	Score(float x, float y, int points);
	void update();
	void draw();
};