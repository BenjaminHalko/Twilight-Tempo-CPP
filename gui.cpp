// https://github.com/BenjaminHalko/Twilight-Tempo/tree/After-Jam/objects/oGUI
#include "gui.h"
#include "global.h"
#include "helper.h"
#include <SFML/Graphics.hpp>

sf::Font GUI::pressStart;
sf::Font GUI::m3x6;

void GUI::init() {
	// May need a failstate
	m3x6.loadFromFile("fonts/m3x6.ttf");
	pressStart.loadFromFile("fonts/press_start.ttf");
}

void GUI::draw() {
	sf::Text text;
	text.setFont(pressStart);
	text.setString(formatScore(Global::score, 4));
	text.setCharacterSize(8);
	text.setFillColor(sf::Color::White); // Set the fill color
	text.setPosition(5, 5);

	Global::render.draw(text);
}