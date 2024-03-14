#include "global.h"
#include "beat_controller.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "score_popup.h"
#include "background.h"

void updateObjects(std::vector<Bullet*>& objects) {
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->update();
		if (objects[i]->isDestroyed()) {
			delete objects[i];
			objects.erase(objects.begin() + i);
			i--;
		}
	}
}

void updateObjects(std::vector<Enemy*>& objects) {
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->update();
		if (objects[i]->isDestroyed()) {
			delete objects[i];
			objects.erase(objects.begin() + i);
			i--;
		}
	}
}

void updateObjects(std::vector<ScorePopup*>& objects) {
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->update();
		if (objects[i]->isDestroyed()) {
			delete objects[i];
			objects.erase(objects.begin() + i);
			i--;
		}
	}
}

void drawObjects(std::vector<Bullet*>& objects) {
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->draw();
	}
}

void drawObjects(std::vector<Enemy*>& objects) {
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->draw();
	}
}

void drawObjects(std::vector<ScorePopup*>& objects) {
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->draw();
	}
}

static void deleteObjects(std::vector<Bullet*>& objects) {
	for (size_t i = 0; i < objects.size(); i++) {
		delete objects[i];
	}
	objects.clear();
}

static void deleteObjects(std::vector<Enemy*>& objects) {
	for (size_t i = 0; i < objects.size(); i++) {
		delete objects[i];
	}
	objects.clear();
}

static void deleteObjects(std::vector<ScorePopup*>& objects) {
	for (size_t i = 0; i < objects.size(); i++) {
		delete objects[i];
	}
	objects.clear();
}

static void deleteSounds() {
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
	deleteObjects(Global::bullets);
	deleteObjects(Global::enemies);
	deleteObjects(Global::scorePopups);
	deleteSounds();

	Global::lives = 12;
	Global::score = 0;
	Global::player = Player(Global::RESW / 2.0, Global::RESH / 2.0);
	Background::init();
}

void startGame() {
	Global::inTutorial = true;
	restartGame();
}