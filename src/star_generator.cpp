#include "star_generator.h"
#include "global.h"
#include "helper.h"
#include <cmath>

std::vector<std::shared_ptr<Star>> StarGenerator::backStars;
std::vector<std::shared_ptr<Star>> StarGenerator::frontStars;

void StarGenerator::init() {
	for (int i = 0; i < 120; i++) {
		std::shared_ptr<Star> s = std::make_shared<Star>();
		s->alpha1 = random_range(0, 1);
		s->alpha2 = random_range(0, 1);
		s->alphaSpd = random_range(1, 5);
		s->alphaOffset = random_range(0, 1);
		backStars.push_back(s);
	}
	for (int i = 0; i < 20; i++) {
		std::shared_ptr<Star> s = std::make_shared<Star>();
		s->alpha1 = random_range(0, 2);
		s->alphaSpd = random_range(0.005f, 0.01f);
		frontStars.push_back(s);
	}
}

void StarGenerator::update() {
	for (const auto & frontStar : frontStars) {
		frontStar->alpha1 += frontStar->alphaSpd;
		if (frontStar->alpha1 > 2) {
			do {
				frontStar->x = random_range(0, Global::RESW);
				frontStar->y = random_range(0, Global::RESH);
			} while (point_distance((float)frontStar->x, (float)frontStar->y, Global::RESW / 2.0f, Global::RESH / 2.0f) < 16);
			frontStar->alpha1 = 0;
			frontStar->alphaSpd = random_range(0.005f, 0.01f);
		}
	}
}

void StarGenerator::drawStarsBack(float alpha) {
	for (const auto & backStar : backStars) {
		sf::Color c = backStar->color;
		c.a = (sf::Uint8)clamp(wave(backStar->alpha1, backStar->alpha2, backStar->alphaSpd, backStar->alphaOffset) * 255.0f * alpha, 0, 255);
		sf::RectangleShape rect(sf::Vector2f(1, 1));
		rect.setPosition(backStar->x, backStar->y);
		rect.setFillColor(c);

		Global::render.draw(rect);
	}
}

void StarGenerator::drawStarsFront(float alpha) {
	for (auto & frontStar : frontStars) {
		sf::Color c = frontStar->color;
		c.a = (sf::Uint8)clamp((1-std::abs(1-frontStar->alpha1)) * 255.0f * alpha, 0, 255);
		sf::RectangleShape rect(sf::Vector2f(1, 1));
		rect.setPosition(frontStar->x, frontStar->y);
		rect.setFillColor(c);
		Global::render.draw(rect);
	}
}
