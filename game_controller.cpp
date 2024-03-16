#include "game_controller.h"
#include "global.h"
#include "beat_controller.h"
#include "player.h"
#include "bullet.h"
#include "score_popup.h"
#include "background.h"
#include "helper.h"

void deleteAll() {
	Global::sounds.clear();
	Global::bullets.clear();
	Global::enemies.clear();
	Global::scorePopups.clear();
	BeatController::stopMusic();
}

void restartGame() {
	deleteAll();

	Global::lives = 12 * (1 + Global::practiceMode);
	Global::score = 0;
	Global::player.init();
	Background::init();
	Shadow::setDarkness(!Global::inTutorial);
}

void startGame() {
	Global::inTutorial = true;
	restartGame();
}