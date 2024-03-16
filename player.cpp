// https://github.com/BenjaminHalko/Twilight-Tempo/tree/After-Jam/objects/oPlayer
#include "player.h"
#include "input.h"
#include "helper.h"
#include "global.h"
#include "beat_controller.h"
#include <stdlib.h>

// Creates the player, and sets all values
Player::Player(float xPos, float yPos) : Object(xPos, yPos, "player/player.png") {
	cannonSprite = Sprite("player/cannon.png");
	cannonSprite().setOrigin(0, 3);
	// Death particles
	std::vector<std::shared_ptr<DeathParticle>> deathParticles;

	init();
}

void Player::init() {
	dir = 0; // Direction the player is pointing
	dirDraw = 0; // Allows the sprite to smoothly turn
	lastDir = -1; // Last known direction by player (SFML detects button being held down)
	shootPercent = 1; // Squash and stretch animation for sprite
	deathSpd = 45;
	dead = false;
	// Amount of shake recieved depending on the direction that the palyer is hit from
	shake[0] = 0;
	shake[1] = 0;
	shake[2] = 0;
	shake[3] = 0;
	generalShake = 0; // Shake from all directions
	cannonMove = 0;
	penalty = 0; // Current pentaly for missed shots
	startScale = 0; // Variable to control opening animation
	// Sprite size
	xscale = 0;
	yscale = 0;
}

void Player::update() {
	if (dead) {
		for (size_t i = 0; i < deathParticles.size(); i++) {
			DeathParticle &particle = *deathParticles[i];
			particle.x += lengthdir_x(particle.spd, particle.dir);
			particle.y += lengthdir_y(particle.spd, particle.dir);
			particle.time++;
			particle.spd = approachEase(particle.spd, 0, 0.01f, 0.9f);
			if (particle.time >= particle.maxTime) {
				deathParticles.erase(deathParticles.begin() + i);
				i--;
			}
		}
	}
	else {
		// If player is alive
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

				bool hit = false;

				for (size_t i = 0; i < Global::enemies.size(); i++) {
					Enemy& enemy = *Global::enemies[i];
					if (((int)enemy.getDirection() % 360) == (dir + 360) % 360) {
						hit = true;
						break;
					}
				}

				if (hit) {
					penalty = 0;
					playSound("enemy_destroy.wav", 33);
					sf::Sound& shootSound = playSound("player_shoot.wav", 18);
					shootSound.setPitch(random_range(0.5f, 1.3f));
				}
				else {
					penalty -= 100;
					Global::scorePopups.push_back(std::make_unique<ScorePopup>(x, y - 20, penalty));
					sf::Sound& shootSound = playSound("player_shoot_fail.ogg", 80);
					shootSound.setPitch(random_range(0.4f, 0.5f));
				}

				// Create bullet
				Global::bullets.push_back(std::make_unique<Bullet>(x + lengthdir_x(bulletLength, (float)dir), y + lengthdir_y(bulletLength, (float)dir), (float)dir));

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
			deathSpd = approachEase(deathSpd, 0, 0.3f, 0.5f);
			dirDraw -= (float)(fmin(30, deathSpd) * 1.5f);
			generalShake = approach(generalShake, (float)fmin(30, deathSpd) / 15.0f, 0.06f);

			if (deathSpd <= 0.001) {
				dead = true;
				playSound("player_explode.wav", 30);
				for (int i = 0; i < 32; i++) {
					for (int j = 0; j < 32; j++) {
						std::shared_ptr<DeathParticle> particle = std::make_unique<DeathParticle>();
						particle->i = i - sprite.getWidth() / 2;
						particle->j = j - sprite.getHeight() / 2;
						particle->x = x + sprite.getWidth() / 2.0f;
						particle->y = y + sprite.getHeight() / 2.0f;
						particle->spd = random_range(0, 4);
						particle->dir = point_direction(15, 15, (float)i, (float)j) + random_range(-20, 20);
						particle->time = 0;
						particle->maxTime = random_range(40, 160);
						deathParticles.push_back(particle);
					}
				}
			}
		}

		cannonMove = approachEase(cannonMove, 0, 0.3f, 0.6f);
		shootPercent = approachEase(shootPercent, 1, 0.1f, 0.6f);
		
		// Start the game
		if (startScale == 1.6f) {
			xscale = approachEase(xscale, 1 + cannonMove / 3.0f * (xscale > 0.75f) + (1 - (float)fmin(30, deathSpd) / 30.0f), 0.05f, 0.3f);
			yscale = approachEase(yscale, 1 + cannonMove / 3.0f * (yscale > 0.75f) + (1 - (float)fmin(30, deathSpd) / 30.0f), 0.05f, 0.3f);
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
					//BeatController::setTrackPos(pos);
				}
			}
		}

		// Reset shake
		for (int i = 0; i < 4; i++) {
			shake[i] = approach(shake[i], 0, 0.06f);
		}
	}
}

void Player::draw() {
	if (dead) {
		sf::Sprite player = sprite();
		for (size_t i = 0; i < deathParticles.size(); i++) {
			DeathParticle particle = *deathParticles[i];
			player.setTextureRect(sf::IntRect(particle.i, particle.j, 1, 1));
			player.setPosition(particle.x, particle.y);
			Global::render.draw(player);
		}
	}
	else {
		sf::Color blend = sf::Color(255, (sf::Uint32)(255.0f * (1 - fmin(1, generalShake / 2))), (sf::Uint32)(255.0f * (1 - fmin(1, generalShake / 2))), 255);

		float _x1 = x + random_range(-shake[0] - generalShake, shake[2] + generalShake);
		float _y1 = y + random_range(-shake[3] - generalShake, shake[1] + generalShake);
		float _x2 = x + random_range(-shake[0] - generalShake, shake[2] + generalShake);
		float _y2 = y + random_range(-shake[3] - generalShake, shake[1] + generalShake);
		_x2 += lengthdir_x(lerp(cannonLength - 1, cannonLength, shootPercent) * xscale - cannonMove * 1.1f, dirDraw);
		_y2 += lengthdir_y(lerp(cannonLength - 1, cannonLength, shootPercent) * yscale - cannonMove * 1.1f, dirDraw);

		sf::Sprite cannon = cannonSprite();
		cannon.setPosition(_x2, _y2);
		cannon.setScale(lerp(0.1f, 1, shootPercent), 1);
		cannon.setRotation(dirDraw);
		cannon.setColor(blend);

		sf::Sprite player = sprite();
		player.setPosition(_x1, _y1);
		player.setScale(xscale * (1 - generalShake / 12.0f), yscale * (1 - generalShake / 12.0f));
		player.setColor(blend);

		Global::render.draw(cannon);
		Global::render.draw(player);
	}
}

// Moving the cannon distance from the player
void Player::setCannonMove(float val) {
	cannonMove = val;
}

void Player::applyShake(int dir) {
	shake[dir] = 2;
	generalShake = 2;
}