// https://github.com/BenjaminHalko/Twilight-Tempo/tree/After-Jam/objects/oScore
#include "score_popup.h"
#include "global.h"

ScorePopup::ScorePopup(float xPos, float yPos, int points) : Object(xPos, yPos) {
	this->points = std::to_string(points);
	Global::score = (int)fmax(0, Global::score + points);
}

void ScorePopup::update() {
	// there is no code here, so destruction must occur
	destroyed = true;
}

void ScorePopup::draw() {

}