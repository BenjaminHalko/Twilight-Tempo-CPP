// https://github.com/BenjaminHalko/Twilight-Tempo/tree/After-Jam/objects/oBullet
#include <SFML/Graphics.hpp>
#include "bullet.h"
#include "global.h"
#include "helper.h"
#include "after_image.h"
#include "beat_controller.h"

Bullet::Bullet(float xPos, float yPos, float dir) : Object(xPos, yPos, "player/bullet.png", 1.0f, 0.5f) {
	direction = dir;
	spd = 8;
	dead = false;
	time = rand() % 60;
	startdir = -1;
	length = 0;
	lastX = x;
	lastY = y;
	waveX = x;
	waveY = y;
	amountOfPoints = (int)(Global::beatTime * 2) % BeatController::BEAT_COUNT;
}

void Bullet::update() {
	for (int i = 0; i < (signed)image.size(); i++) {
		image[i].alpha -= 0.15f * 255.0f;
		if (image[i].alpha <= 0) {
			image.erase(image.begin() + i);
			i--;
		}
	}

	if (spd != 0) {
		int _from = startdir - 5;
		int _to = startdir + 5;
		int i = 0;
		for (i = 0; i < 4; i++) {
			x += lengthdir_x(spd, direction);
			y += lengthdir_y(spd, direction);
			image.push_back(AfterImage(x, y, direction));
			if (spd == 0)
				break;
		}		

		for (int j = 0; j < fmin(i + 1, 3); j++) {
			waveX += lengthdir_x(8, direction);
			waveY += lengthdir_y(8, direction);

			float _wave = (float)((_from + (_to - _from) * 0.5 + sin(((time / 60.0f + 0.15f * 0.3f) / 0.15f) * (PI * 2.0f)) * (_to - _from) * 0.5f) * fmin(1, time / 2.0f));

			float _x = waveX + lengthdir_x(_wave, direction + 90);
			float _y = waveY + lengthdir_y(_wave, direction + 90);

			image.push_back(AfterImage(_x, _y, point_direction(lastX, lastY, x, y)));
			lastX = _x;
			lastY = _y;

			time++;
		}

		if (x < -16 || x > Global::RESW + 16 || y < -16 || y > Global::RESH + 16) {
			spd = 0;
		}
	}
	else if (image.size() == 0) {
		destroyed = true;
	}
}

void Bullet::draw() {
	sf::Sprite spr = sprite();
	for (int i = 0; i < (signed)image.size(); i++) {
		spr.setPosition(image[i].x, image[i].y);
		spr.setRotation(image[i].dir);
		spr.setColor(sf::Color(255, 255, 255, (sf::Uint8)image[i].alpha));
		Global::render.draw(spr);
	}
}