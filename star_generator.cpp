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


void StarGenerator::drawStarsFront() {

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