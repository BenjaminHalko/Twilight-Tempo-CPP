// https://github.com/BenjaminHalko/Twilight-Tempo/tree/After-Jam/objects/oBackground
#include "background.h"
#include "helper.h"
#include "global.h"
#include "star_generator.h"
#include "beat_controller.h"
#include "shadow.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Sprite Background::backgroundSprite[4] = {
	Sprite("background/0.png"),
	Sprite("background/1.png"),
	Sprite("background/2.png"),
	Sprite("background/3.png"),
};

Sprite Background::cloudSprite = Sprite("background/clouds.png");

int Background::backgroundIndex = 0;
bool Background::isNight = false;
int Background::timer = 30;

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

void Background::init() {
	isNight = !Global::inTutorial;
	backgroundIndex = isNight * 8;
	timer = 30;
}

void Background::update() {
	if (Global::inTutorial && Global::enemies.empty() && BeatController::getBarNumber() == 9)
		isNight = true;

	if ((backgroundIndex != isNight * 8 || timer != 30) && --timer <= 0) {
		if (backgroundIndex == 8) {
			BeatController::resetSong();
			timer = 30;
		}
		else {
			if (backgroundIndex >= 4)
				Shadow::setDarkness((float)(backgroundIndex - 3) / 4.0f);
			backgroundIndex++;
			timer = 30;
			if (backgroundIndex == 8) {
				Global::inTutorial = false;
				Global::score = 0;
				Global::lives = 12 * (1 + Global::practiceMode);
				timer--;
			}
		}
	}
}

void Background::draw() {
	Global::render.clear(backgroundColors[(int)fmin(3, backgroundIndex)]);

	if (backgroundIndex != 0) {
		StarGenerator::drawStarsBack((float)backgroundIndex / 4.0f);
	}

	sf::Sprite cloud = cloudSprite();
	cloud.setColor(cloudColors[(int)fmin(4, backgroundIndex)]);
	Global::render.draw(cloud);

	if (backgroundIndex < 4) {
		sf::Sprite background = backgroundSprite[backgroundIndex]();
		Global::render.draw(background);
	}
}
