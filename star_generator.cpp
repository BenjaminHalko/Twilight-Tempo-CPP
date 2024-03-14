#include "star_generator.h"
#include "global.h"
#include "helper.h"

std::vector<Star*> StarGenerator::backStars;
std::vector<Star*> StarGenerator::frontStars;

void StarGenerator::init() {
	for (int i = 0; i < 120; i++) {
		Star* s = new Star();
		s->x = rand() % Global::RESW;
		s->y = rand() % Global::RESH;
		s->color = (rand() % 2) ? hexColor(0xd2de8e) : hexColor(0x60205a);
		s->alpha1 = random_range(0, 1);
		s->alpha2 = random_range(0, 1);
		s->alphaSpd = random_range(1, 5);
		s->alphaOffset = random_range(0, 1);
		backStars.push_back(s);
	}
	for (int i = 0; i < 20; i++) {
		Star* s = new Star();
		s->x = rand() % Global::RESW;
		s->y = rand() % Global::RESH;
		s->color = (rand() % 2) ? hexColor(0xd2de8e) : hexColor(0x60205a);
		s->alpha1 = random_range(0, 2);
		s->alphaSpd = random_range(0.005f, 0.01f);
		frontStars.push_back(s);
	}
}

void StarGenerator::update() {
	for (size_t i = 0; i < frontStars.size(); i++) {
		Star* s = frontStars[i];
		s->alpha1 += s->alphaSpd;
		if (s->alpha1 > 2) {
			do {
				s->x = rand() % Global::RESW;
				s->y = rand() % Global::RESH;
			} while (point_distance((float)s->x, (float)s->y, Global::RESW / 2.0f, Global::RESH / 2.0f) < 16);
			s->alpha1 = 0;
			s->alphaSpd = random_range(0.005f, 0.01f);
		}
	}
}

void StarGenerator::drawStarsBack(float alpha) {
	for (size_t i = 0; i < backStars.size(); i++) {
		Star* s = backStars[i];
		sf::Color c = s->color;
		c.a = (sf::Uint8)(wave(s->alpha1, s->alpha2, s->alphaSpd, s->alphaOffset) * 255.0f * alpha);
		sf::RectangleShape rect(sf::Vector2f(1, 1));
		rect.setPosition((float)s->x, (float)s->y);
		rect.setFillColor(c);

		Global::render.draw(rect);
	}
}


void StarGenerator::drawStarsFront(float alpha) {
	for (size_t i = 0; i < frontStars.size(); i++) {
		Star* s = frontStars[i];
		sf::Color c = s->color;
		c.a = (sf::Uint8)((1-abs(1-s->alpha1)) * 255.0f * alpha);
		sf::RectangleShape rect(sf::Vector2f(1, 1));
		rect.setPosition((float)s->x, (float)s->y);
		rect.setFillColor(c);
		Global::render.draw(rect);
	}
}

void StarGenerator::deleteStars() {
	for (size_t i = 0; i < backStars.size(); i++) {
		delete backStars[i];
	}

	for (size_t i = 0; i < frontStars.size(); i++) {
		delete frontStars[i];
	}

	backStars.clear();
	frontStars.clear();
}