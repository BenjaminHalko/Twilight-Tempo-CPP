// https://github.com/BenjaminHalko/Twilight-Tempo/tree/After-Jam/objects/oEnemy
#include "enemy.h"
#include "global.h"
#include "beat_controller.h"
#include "helper.h"
#include <SFML/Graphics.hpp>

Enemy::Enemy(float xPos, float yPos, float dir) : Object(xPos, yPos, "enemy/enemy.png") {
	direction = dir;
	dead = false;
	deadPercent = 0;
	hit = false;
	circlePercent = 0;
	speed = (float)(- 3 - Global::hardMode);
	timePoints = (int)((Global::beatTime + BeatController::aheadTime) * 2) % BeatController::BEAT_COUNT;
	flash = false;
	flashSprite = Sprite("enemy/enemy_flash.png", 0.5, 0.5);
	cornerSprite = Sprite("enemy/enemy_spike.png", 0, 0.5);
	angle = 0;
	alpha = 255.0f;
}

void Enemy::update() {
	if (dead) {
		speed = 0;
		deadPercent = approach(deadPercent, 1, 0.1f);
		circlePercent = approach(circlePercent, 1, 0.05f);

		if (circlePercent == 1) {
			destroyed = true;
		}
	}

	if (hit || Global::lives <= 0) {
		if (hit) {
			flash = true;
			xscale += 0.05f;
			yscale += 0.05f;
			speed *= 0.7f;
			alpha -= 0.2f * 255.0f;
			angle -= 20;
		}
		else {
			speed = approachEase(speed, 0, 0.1f, 0.6f);
			alpha -= 0.05f * 255.0f;
		}

		if (alpha <= 0) {
			destroyed = true;
		}	
	}

	x += lengthdir_x(speed, direction);
	y += lengthdir_y(speed, direction);

	if (!hit && !dead && Global::lives > 0) {
		if (isColliding(Global::player)) {
			//Global::lives--;
			hit = true;
			Global::player.applyShake((int)direction / 90);
			sf::Sound& hitNoise = playSound("player_hurt.wav", 100)();
			hitNoise.setPitch(random_range(0.8f, 1.2f));
			if (Global::lives == 0) {
				playSound("player_die.wav", 100);
			}
		}
	}
}

void Enemy::draw() {
	sf::Sprite spr = (flash) ? flashSprite() : sprite();
	sf::Sprite corner = cornerSprite();

	for(int i = 0; i < 4; i++) {
		float _length = lerp(wave(4.0f, 6.0f, 0.5f, i / 4.0f), 10, deadPercent);
		corner.setPosition(x + lengthdir_x(_length, (float)(45 + i * 90)), y + lengthdir_y(_length, (float)(45 + i * 90)));
		corner.setRotation((float)(45 + i * 90));
		
		corner.setColor(sf::Color(255, 255, 255, (sf::Uint8)((1 - deadPercent) * 255.0f)));
		Global::render.draw(corner);
	}

	if (!dead) {
		spr.setPosition(x, y);
		spr.setScale(xscale, yscale);
		spr.setColor(sf::Color(255, 255, 255, (sf::Uint8)(alpha)));
		spr.setRotation(angle);
		Global::render.draw(spr);
	}

}

void Enemy::killEnemy() {
	dead = true;
	speed = 0;
}

bool Enemy::isDead() {
	return dead;
}