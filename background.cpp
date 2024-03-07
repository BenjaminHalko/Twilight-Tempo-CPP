// https://github.com/BenjaminHalko/Twilight-Tempo/tree/After-Jam/objects/oBackground
#include "background.h"
#include "helper.h"
#include <SFML/Graphics.hpp>

Background::Background() {
	// Set Sprites
	backgroundSprite[0] = Sprite("background/0.png");
	backgroundSprite[1] = Sprite("background/1.png");
	backgroundSprite[2] = Sprite("background/2.png");
	backgroundSprite[3] = Sprite("background/3.png");
	cloudSprite = Sprite("background/clouds.png");

	// Set Colors
	backgroundColors[0] = hexColor(0x251932);
	backgroundColors[1] = hexColor(0x1C1329);
	backgroundColors[2] = hexColor(0x151022);
	backgroundColors[3] = hexColor(0x0B0A19);
	cloudColors[0] = hexColor(0x3A264A);
	cloudColors[1] = hexColor(0x302143);
	cloudColors[2] = hexColor(0x281D3E);
	cloudColors[3] = hexColor(0x211A3A);
	cloudColors[4] = hexColor(0x161433);

	// Set other variables
	updateBG(0);
}

void Background::updateBG(int index) {
	backgroundIndex = index;
}

void Background::draw(sf::RenderWindow &window) {
	window.clear(backgroundColors[backgroundIndex]);

	sf::Sprite background = backgroundSprite[backgroundIndex]();
	sf::Sprite cloud = cloudSprite();
	cloud.setColor(cloudColors[backgroundIndex]);

	window.draw(cloud);
	window.draw(background);
}