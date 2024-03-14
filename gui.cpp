// https://github.com/BenjaminHalko/Twilight-Tempo/tree/After-Jam/objects/oGUI
#include "gui.h"
#include "global.h"
#include "helper.h"
#include "sprite.h"
#include <SFML/Graphics.hpp>

std::vector<Sprite*> GUI::hearts;
std::vector<float> GUI::heartScale(3, 1);
std::vector<float> GUI::warningPulse(4, 0);

void GUI::init() {
	for (int i = 0; i < 9; i++) {
		hearts.push_back(new Sprite("gui/health/" + std::to_string(i) + ".png", 0.55f, 0.55f));
	}
}

void GUI::clean() {
	for (size_t i = 0; i < hearts.size(); i++) {
		delete hearts[i];
	}
}

void GUI::update() {
	// Update heart scale
	for (int i = 0; i < 3; i++) {
		heartScale[i] = approach(heartScale[i], 1, 0.05f);
	}

	// Update warning pulses
	for (int i = 0; i < 4; i++) {
		warningPulse[i] = approach(warningPulse[i], 0, 0.1f);
	}
}

void GUI::draw() {
	drawText("SCORE:", 6, 6);
	drawText("   " + formatScore(Global::score, 4), 6, 15);
	if (Global::inTutorial) {
		drawText("TUTORIAL", Global::RESW/2, 6, true);
		drawText("LEVEL", Global::RESW / 2, 15, true);
	}
	else if(Global::practiceMode) {
		drawText("PRACTICE", Global::RESW / 2, 6, true);
		drawText("MODE", Global::RESW / 2, 15, true);
	}
	else {
		drawText("HIGH SCORE:", Global::RESW / 2, 6, true);
		drawText(formatScore(Global::highScore, 5), Global::RESW / 2, 15, true);
	}

	for (int i = 0; i < 3; i++) {
		sf::Sprite heart = (*hearts[(int)clamp((float)(Global::lives - i * 4 * (1 + Global::practiceMode)) * (2 - Global::practiceMode), 0, 8)])();

		heart.setPosition((float)(Global::RESW - 10 - i * 14), 10);
		heart.setScale(heartScale[i], heartScale[i]);
		Global::render.draw(heart);
	}
}

void GUI::pulseHeart() {
	heartScale[Global::lives / (4 * (1 + Global::practiceMode))] = 1.4f;
}

void GUI::pulseWarning(int i) {
	warningPulse[i] = 1;
}