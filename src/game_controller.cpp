#include "game_controller.h"
#include "global.h"
#include "beat_controller.h"
#include "background.h"
#include "shadow.h"

void deleteAll() {
	Global::bullets.clear();
	Global::enemies.clear();
	Global::scorePopups.clear();
	BeatController::stopMusic();
}

void startGame() {
	deleteAll();

	Global::lives = 12 * (1 + Global::practiceMode);
	Global::score = 0;
	Global::player.init();
	Background::init();
	Shadow::setDarkness(!Global::inTutorial);
}

