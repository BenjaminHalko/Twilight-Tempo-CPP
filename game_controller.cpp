#include "global.h"
#include "beat_controller.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "score.h"

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

void updateObjects(std::vector<Score*>& objects) {
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

void drawObjects(std::vector<Score*>& objects) {
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

static void deleteObjects(std::vector<Score*>& objects) {
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
	deleteObjects(Global::scoreObjects);
	deleteSounds();
}

void startGame() {
	deleteObjects(Global::bullets);
	deleteObjects(Global::enemies);
	deleteObjects(Global::scoreObjects);
	deleteSounds();

	Global::lives = 8;
	Global::score = 0;
	Global::inTutorial = false;
	Global::hardMode = false;

	Global::player = Player(Global::RESW / 2.0, Global::RESH / 2.0);
}