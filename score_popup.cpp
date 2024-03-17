// https://github.com/BenjaminHalko/Twilight-Tempo/tree/After-Jam/objects/oScore
#include "score_popup.h"
#include "global.h"
#include "helper.h"

ScorePopup::ScorePopup(float xPos, float yPos, int points) : Object(xPos, yPos) {
	alpha = 1;
	this->points = std::to_string(points);
	Global::score = (int)fmax(0, Global::score + points);
}

void ScorePopup::update() {
	alpha -= 0.05f;
	if (alpha <= 0)
		destroyed = true;
}

void ScorePopup::draw() {
	sf::Color col = sf::Color::White;
	col.a = (sf::Uint8)(255.0f * alpha);
	drawText(points, (int)x, (int)(y - floor((1-alpha) * 3)), true, true, true, col);
}
