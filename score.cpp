#include "score.h"
#include "global.h"

Score::Score(float xPos, float yPos, int points) : Object(xPos, yPos) {
	this->points = std::to_string(points);
	Global::score += points;
}

void Score::update() {
	// there is no code here, so destruction must occur
	destroyed = true;
}

void Score::draw() {

}