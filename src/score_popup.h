#pragma once
#include "object.h"
class ScorePopup : public Object {
private:
	std::string points;
	float alpha;
public:
	ScorePopup(float x, float y, int points);
	void update() override;
	void draw() override;
};
