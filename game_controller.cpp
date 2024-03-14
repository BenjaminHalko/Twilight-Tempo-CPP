#include "game_controller.h"
#include "global.h"
#include "beat_controller.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "score_popup.h"
#include "background.h"
#include "helper.h"

void deleteSounds() {
	for (size_t i = 0; i < Global::sounds.size(); i++) {
		delete Global::sounds[i];
	}
	Global::sounds.clear();
	BeatController::stopMusic();
}

void cleanUp() {
	deleteObjects(Global::bullets);
	deleteObjects(Global::enemies);
	deleteObjects(Global::scorePopups);
	deleteSounds();
}

void restartGame() {
	cleanUp();

	Global::lives = 12 * (1 + Global::practiceMode);
	Global::score = 0;
	Global::player = Player(Global::RESW / 2.0, Global::RESH / 2.0);
	Background::init();
	Shadow::setDarkness(!Global::inTutorial);
}

void startGame() {
	Global::inTutorial = true;
	restartGame();
}