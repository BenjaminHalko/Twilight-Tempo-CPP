// https://github.com/BenjaminHalko/Twilight-Tempo/tree/After-Jam/objects/oPlayer
#include "player.h"
#include "input.h"
#include "helper.h"
#include "global.h"
#include "beat_controller.h"
#include <stdlib.h>

Player::Player(float xPos, float yPos) : Object(xPos, yPos, "player/player.png") {
	cannonSprite = Sprite("player/cannon.png");
	cannonSprite().setOrigin(0, 3);
	dir = 0;
	dirDraw = 0;
	lastDir = -1;
	shootPercent = 1;
	shake[0] = 0;
	shake[1] = 0;
	shake[2] = 0;
	shake[3] = 0;
	generalShake = 0;
	cannonMove = 0;
	penalty = 0;
	startScale = 0;
	xscale = 0;
	yscale = 0;
}

void Player::update() {
	
	if (Global::lives > 0) {
		// Input
		bool key_left = inputLeft();
		bool key_right = inputRight();
		bool key_up = inputUp();
		bool key_down = inputDown();

		// Direction
		bool shoot = false;
		if (abs(key_right - key_left) != abs(key_down - key_up)) {
			dir = (int)point_direction(0, 0, (float)key_right - key_left, (float)key_down - key_up);
			if (dir != lastDir) {
				lastDir = dir;
				shoot = true;
			}
		}
		else {
			lastDir = -1;
		}

		// Shooting
		if (shoot) {

			Sound& shootSound = playSound("player_shoot.wav", 18);
			shootSound().setPitch(0.8f + random_range(-0.1f, 0.1f));


			if ((dir / 90) % 2 == 0) {
				xscale = 0.3f;
			}
			else {
				yscale = 0.3f;
			}

			shootPercent = 0;
		}
		dirDraw = approachCircleEase(dirDraw, (float)dir, 50, 0.6f);
		generalShake = approach(generalShake, 0, 0.06f);
	}
	else {
		// TODO
	}

	cannonMove = approachEase(cannonMove, 0, 0.3f, 0.6f);
	shootPercent = approachEase(shootPercent, 1, 0.1f, 0.6f);

	if (startScale == 1.6f) {
		xscale = approachEase(xscale, 1+cannonMove/3.0f*(xscale > 0.75f)+(1-(float)fmin(30, deathSpd)/30.0f), 0.05f, 0.3f);
		yscale = approachEase(yscale, 1+cannonMove/3.0f*(yscale > 0.75f)+(1-(float)fmin(30, deathSpd)/30.0f), 0.05f, 0.3f);
	}
	else {
		startScale = approach(startScale, 1.6f, 0.05f);
		xscale = bezierCurve((float)fmin(1, startScale));
		yscale = xscale;

		if (startScale == 1.6f) {
			if (Global::inTutorial) {
				BeatController::resetSong();
			}
			else {
				BeatController::resetSong();
				float trackPositions[] = { 0, 29.53f, 66.46f };
				float pos = trackPositions[rand() % 3] * 130.0f / BeatController::getBPM();
				// BeatController::setTrackPos(pos);
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		shake[i] = approach(shake[i], 0, 0.06f);
	}
}

void Player::draw() {
	float _x1 = x + random_range(-shake[0]-generalShake, shake[2]+generalShake);
	float _y1 = y + random_range(-shake[3]-generalShake, shake[1]+generalShake);
	float _x2 = x + random_range(-shake[0] - generalShake, shake[2] + generalShake);
	float _y2 = y + random_range(-shake[3] - generalShake, shake[1] + generalShake);
	_x2 += lengthdir_x(lerp(cannonLength - 1, cannonLength, shootPercent) * xscale - cannonMove * 1.1f, dirDraw);
	_y2 += lengthdir_y(lerp(cannonLength - 1, cannonLength, shootPercent) * yscale - cannonMove * 1.1f, dirDraw);

	sf::Sprite cannon = cannonSprite();
	cannon.setPosition(_x2, _y2);
	cannon.setScale(lerp(0.1f, 1, shootPercent), 1);
	cannon.setRotation(dirDraw);

	sf::Sprite player = sprite();
	player.setPosition(_x1, _y1);
	player.setScale(xscale * (1 - generalShake / 12.0f), yscale * (1 - generalShake / 12.0f));

	Global::window.draw(cannon);
	Global::window.draw(player);
}

void Player::setCannonMove(float val) {
	cannonMove = val;
}