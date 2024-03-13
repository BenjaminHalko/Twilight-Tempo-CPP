// https://github.com/BenjaminHalko/Twilight-Tempo/tree/After-Jam/objects/oGUI
#include "gui.h"
#include "global.h"
#include "helper.h"
#include "sprite.h"
#include <SFML/Graphics.hpp>

sf::Font GUI::pressStart;
sf::Font GUI::m3x6;
std::vector<Sprite*> GUI::hearts;
std::vector<float> GUI::heartScale;

void GUI::init() {
	// May need a failstate
	m3x6.loadFromFile("fonts/m3x6.ttf");
	pressStart.loadFromFile("fonts/press_start.ttf");
	heartScale = { 1, 1, 1 };

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
}

void GUI::draw() {
	drawText(pressStart, "SCORE:", 8, 6, 6, false, false);
	drawText(pressStart, "   " + formatScore(Global::score, 4), 8, 6, 15, false, false);
	if (Global::inTutorial) {
		drawText(pressStart, "TUTORIAL", 8, Global::RESW/2, 6, true, false);
		drawText(pressStart, "LEVEL", 8, Global::RESW / 2, 15, true, false);
	}
	else if(true) {
		drawText(pressStart, "PRACTICE", 8, Global::RESW / 2, 6, true, false);
		drawText(pressStart, "MODE", 8, Global::RESW / 2, 15, true, false);
	}
	else {
		drawText(pressStart, "HIGH SCORE:", 8, Global::RESW / 2, 6, true, false);
		drawText(pressStart, formatScore(Global::score, 5), 8, Global::RESW / 2, 15, true, false);
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