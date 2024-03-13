// https://github.com/BenjaminHalko/Twilight-Tempo/tree/After-Jam/objects/oGUI
#include "gui.h"
#include "global.h"
#include "helper.h"
#include "sprite.h"
#include <SFML/Graphics.hpp>

sf::Font GUI::pressStart;
sf::Font GUI::m3x6;

void GUI::init() {
	// May need a failstate
	m3x6.loadFromFile("fonts/m3x6.ttf");
	pressStart.loadFromFile("fonts/press_start.ttf");
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
		
	}
	
}

void GUI::drawText(sf::Font font, std::string textString, int characterSize, int x, int y, bool horizCentered, bool vertCentered, sf::Color colour) {
	sf::Text text;
	text.setFont(font);
	text.setString(textString);
	text.setCharacterSize(characterSize);
	text.setPosition(x - (int)(horizCentered * (text.getGlobalBounds().width/2)), y - (int)(vertCentered * (text.getGlobalBounds().height/2)));
	text.setFillColor(colour); // Set the fill color

	Global::render.draw(text);
}