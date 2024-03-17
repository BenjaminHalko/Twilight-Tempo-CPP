// https://github.com/BenjaminHalko/Twilight-Tempo/tree/After-Jam/objects/oShadow
#include "shadow.h"
#include "global.h"
#include "helper.h"
#include "star_generator.h"

sf::RenderTexture Shadow::shadow;
const sf::BlendMode Shadow::blendSubtractive = sf::BlendMode(sf::BlendMode::Zero, sf::BlendMode::OneMinusSrcColor);
float Shadow::darkness = 1;
float Shadow::radius = 0;

void Shadow::init() {
	shadow.create(Global::RESW, Global::RESH);
}

void Shadow::update() {
	radius = approach(radius, 0, 0.1f);
}

void Shadow::draw() {
	sf::Sprite renderSprite(shadow.getTexture());
	renderSprite.setPosition(0, Global::RESH);
	renderSprite.setScale(1, -1);
	renderSprite.setColor(sf::Color(255, 255, 255, (sf::Uint8)(255.0f * darkness)));
	Global::render.draw(renderSprite);
	shadow.clear(sf::Color::Black);
	drawCircle(Global::RESW / 2.0f, Global::RESH / 2.0f, 16, 1 + radius * 0.7f);
	StarGenerator::drawStarsFront(darkness);
}

void Shadow::drawCircle(float x, float y, float radius, float alpha) {
	sf::CircleShape circle;
	for (int i = 0; i < 6; i++) {
		circle.setRadius(radius + i * 3);
		circle.setPosition(x - radius - i * 3, y - radius - i * 3);
		circle.setFillColor(sf::Color(0, 0, 0, (sf::Uint8)(255.0f * (0.8 - i * 0.1) * alpha)));
		shadow.draw(circle, blendSubtractive);
	}
	circle.setRadius(radius);
	circle.setPosition(x - radius, y - radius);
	circle.setFillColor(sf::Color(0, 0, 0, (sf::Uint8)(255.0f * 0)));
	shadow.draw(circle, blendSubtractive);
}

void Shadow::setDarkness(float dark) {
	darkness = dark;
}

void Shadow::setRadius(float rad) {
	radius = rad;
}
