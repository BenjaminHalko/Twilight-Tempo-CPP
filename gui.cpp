// https://github.com/BenjaminHalko/Twilight-Tempo/tree/After-Jam/objects/oGUI
#include "gui.h"
#include "global.h"
#include "helper.h"
#include "sprite.h"
#include "input.h"
#include "title.h"
#include "game_controller.h"
#include <SFML/Graphics.hpp>

std::vector<std::shared_ptr<Sprite>> GUI::hearts;
std::vector<float> GUI::heartScale(3, 1);
std::vector<float> GUI::warningPulse(4, 0);
int GUI::timer = 0;
float GUI::gameOverTimer = 0;
bool GUI::gameOverChoice = false;
int GUI::newRecord = 0;
bool GUI::menuHeldInput = false;

void GUI::init() {
	for (int i = 0; i < 9; i++) {
		hearts.push_back(std::make_unique<Sprite>("gui/health/" + std::to_string(i) + ".png", 0.5f, 0.5f));
	}
}

void GUI::update() {
	// Game over menu
	if (gameOverTimer > 0) {
		if (gameOverTimer > 20 || inputConfirm()) {
			if (gameOverTimer > 20 || gameOverChoice)
				Title::goToTitle();
			else
				restartGame();
			gameOverTimer = 0;
			gameOverChoice = false;
			timer = 30;
			newRecord = 0;
		}
		else if (inputDown() || inputUp() || inputLeft() || inputRight()) {
			if (!menuHeldInput) {
				gameOverChoice = !gameOverChoice;
				playSound("blip.ogg", 100);
				menuHeldInput = true;
			}
		}
		else {
			menuHeldInput = false;
		}
	}
	if (Global::player.isDestroyed() && --timer <= 0) {
		if (newRecord != 0)
			newRecord++;

		if (!Global::practiceMode) {
			if (gameOverTimer == 0 && !Global::inTutorial && Global::score > Global::highScore) {
				newRecord++;
				Global::highScore = Global::score;
				save(Global::hardMode ? "hard" : "normal", Global::highScore);
			}
		}

		gameOverTimer += 0.5f;
		timer = 30;
	}

	// Update heart scale
	for (int i = 0; i < 3; i++) {
		heartScale[i] = approach(heartScale[i], 1, 0.05f);
	}

	// Update warning pulses
	for (int i = 0; i < 4; i++) {
		warningPulse[i] = approach(warningPulse[i], 0, 0.1f);
	}
}

void GUI::draw() {
	drawText("SCORE:", 6, 6);
	drawText("  " + formatScore(Global::score, 4), 6, 15);
	if (Global::inTutorial) {
		drawText("TUTORIAL", Global::RESW/2, 6, true);
		drawText("LEVEL", Global::RESW / 2, 15, true);
	}
	else if(Global::practiceMode) {
		drawText("PRACTICE", Global::RESW / 2, 6, true);
		drawText("MODE", Global::RESW / 2, 15, true);
	}
	else {
		drawText("HIGH SCORE:", Global::RESW / 2, 6, true);
		drawText(formatScore(Global::highScore, 5), Global::RESW / 2, 15, true);
	}

	for (int i = 0; i < 3; i++) {
		sf::Sprite heart = (*hearts[(int)clamp((float)(Global::lives - i * 4 * (1 + Global::practiceMode)) * (2 - Global::practiceMode), 0, 8)])();

		heart.setPosition((float)(Global::RESW - 10 - i * 14), 10);
		heart.setScale(heartScale[i], heartScale[i]);
		Global::render.draw(heart);
	}

	// Game over menu
	if (gameOverTimer > 0) {
		drawText("GAME OVER", Global::RESW / 2, Global::RESH / 2 - 35, true, true, false, sf::Color::White, 2);

		if (newRecord % 2)
			drawText("NEW RECORD", Global::RESW / 2, 30, true, true, false, sf::Color::Red);

		drawText("CONTINUE?", Global::RESW / 2, Global::RESH / 2, true, true);
		drawText(std::to_string(20-(int)ceil(gameOverTimer)), Global::RESW / 2, Global::RESH / 2 + 20, true, true);

		if (!gameOverChoice) {
			drawText(">YES", Global::RESW / 2 - 38, Global::RESH / 2 + 40, true, true);
			drawText("NO", Global::RESW / 2 + 32, Global::RESH / 2 + 40, true, true);
		}
		else {
			drawText("YES", Global::RESW / 2 - 34, Global::RESH / 2 + 40, true, true);
			drawText(">NO", Global::RESW / 2 + 27, Global::RESH / 2 + 40, true, true);
		}
	}
}

void GUI::pulseHeart() {
	heartScale[Global::lives / (4 * (1 + Global::practiceMode))] = 1.4f;
}

void GUI::pulseWarning(int i) {
	warningPulse[i] = 1;
}
