#include "global.h"
#include "beat_controller.h"
#include "player.h"

void startGame() {
	BeatController::stopMusic();
	
	Global::lives = 12;
	Global::score = 0;
	Global::inTutorial = false;
	Global::hardMode = false;

	Global::player = Player(Global::RESW / 2.0, Global::RESH / 2.0);
}