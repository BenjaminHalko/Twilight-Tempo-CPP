#pragma once
#include "bullet.h"
#include "enemy.h"
#include "score_popup.h"
void startGame();
void restartGame();
void deleteSounds();
void cleanUp();

template<typename T>
void updateObjects(std::vector<T*>& objects) {
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->update();
		if (objects[i]->isDestroyed()) {
			delete objects[i];
			objects.erase(objects.begin() + i);
			i--;
		}
	}
}

template<typename T>
void drawObjects(std::vector<T*>& objects) {
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->draw();
	}
}

template<typename T>
void deleteObjects(std::vector<T*>& objects) {
	for (size_t i = 0; i < objects.size(); i++) {
		delete objects[i];
	}
	objects.clear();
}