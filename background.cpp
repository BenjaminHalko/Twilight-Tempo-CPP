// https://github.com/BenjaminHalko/Twilight-Tempo/tree/After-Jam/objects/oBackground
#include "background.h"
#include "helper.h"
#include <SFML/Graphics.hpp>
#include "global.h"

Sprite Background::backgroundSprite[4] = {
	Sprite("background/0.png"),
	Sprite("background/1.png"),
	Sprite("background/2.png"),
	Sprite("background/3.png"),
};

Sprite Background::cloudSprite = Sprite("background/clouds.png");

int Background::backgroundIndex = 4;

sf::Color Background::backgroundColors[4] = {
	hexColor(0x251932),
	hexColor(0x1C1329),
	hexColor(0x151022),
	hexColor(0x0B0A19),
};

sf::Color Background::cloudColors[5] = {
	hexColor(0x3A264A),
	hexColor(0x302143),
	hexColor(0x281D3E),
	hexColor(0x211A3A),
	hexColor(0x161433),
};	

void Background::updateBG(int index) {
	backgroundIndex = index;
}

void Background::draw() {
	Global::render.clear(backgroundColors[(int)fmin(3, backgroundIndex)]);

	sf::Sprite cloud = cloudSprite();
	cloud.setColor(cloudColors[backgroundIndex]);
	Global::render.draw(cloud);

	if (backgroundIndex < 4) {
		sf::Sprite background = backgroundSprite[backgroundIndex]();
		Global::render.draw(background);
	}
}