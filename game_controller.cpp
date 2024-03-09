#include "global.h"
#include "beat_controller.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"

void startGame() {
	BeatController::stopMusic();
	
	Global::lives = 12;
	Global::score = 0;
	Global::inTutorial = false;
	Global::hardMode = false;

	Global::player = Player(Global::RESW / 2.0, Global::RESH / 2.0);
}


void updateObjects(std::vector<Bullet*>& objects) {
	for (int i = 0; i < (signed)objects.size(); i++) {
		objects[i]->update();
		if (objects[i]->isDestroyed()) {
			delete objects[i];
			objects.erase(objects.begin() + i);
			i--;
		}
	}
}

void updateObjects(std::vector<Enemy*>& objects) {
	for (int i = 0; i < (signed)objects.size(); i++) {
		objects[i]->update();
		if (objects[i]->isDestroyed()) {
			delete objects[i];
			objects.erase(objects.begin() + i);
			i--;
		}
	}
}

void drawObjects(std::vector<Bullet*>& objects) {
	for (int i = 0; i < (signed)objects.size(); i++) {
		objects[i]->draw();
	}
}

void drawObjects(std::vector<Enemy*>& objects) {
	for (int i = 0; i < (signed)objects.size(); i++) {
		objects[i]->draw();
	}
}