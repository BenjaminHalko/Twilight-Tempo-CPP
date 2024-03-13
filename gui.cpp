// https://github.com/BenjaminHalko/Twilight-Tempo/tree/After-Jam/objects/oGUI
#include "gui.h"
#include "global.h"
#include "helper.h"
#include "sprite.h"
#include <SFML/Graphics.hpp>

sf::Font GUI::pressStart;
sf::Font GUI::m3x6;
std::vector<Sprite*> GUI::hearts;

void GUI::init() {
	// May need a failstate
	m3x6.loadFromFile("fonts/m3x6.ttf");
	pressStart.loadFromFile("fonts/press_start.ttf");

	for (size_t i = 0; i < 9; i++)
	{
		hearts.push_back(new Sprite("gui/health/" + std::to_string(i) + ".png"));
	}
}

void GUI::draw() {
	drawText(pressStart, "SCORE:\n   " + formatScore(Global::score, 4), 8, 6, 6, false, false);
	if (Global::inTutorial) {
		drawText(pressStart, "TUTORIAL", 8, Global::RESW/2, 6, true, false);
		drawText(pressStart, "LEVEL", 8, Global::RESW / 2, 14, true, false);
	}
	/*
	else if(true) {
		drawText(pressStart, "PRACTICE\n  MODE", 8, Global::RESW / 2, 6, true, false);
	}
	*/
	else {
		drawText(pressStart, "HIGH SCORE:", 8, Global::RESW / 2, 6, true, false);
		drawText(pressStart, formatScore(Global::score, 5), 8, Global::RESW / 2, 14, true, false);
	}

	for (size_t i = 0; i < 3; i++) {
		sf::Sprite heart = (*hearts[clamp(Global::lives - i * 4 * (1 + Global::practiceMode) * (2 - Global::practiceMode), 0, 8)])();

		heart.setPosition(Global::RESW - 10 - i * 14, 10);
		heart.setScale(heartScale[i], heartScale[i]);
		Global::render.draw(heart);
	}
	

	sf::Sprite mySprite = (*hearts[0])();
}