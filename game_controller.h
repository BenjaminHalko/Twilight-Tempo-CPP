#pragma once
#include "bullet.h"
#include "enemy.h"
#include "score_popup.h"
void startGame();
void restartGame();
void deleteAll();

template<typename T>
void updateObjects(std::vector<std::shared_ptr<T>>& objects) {
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->update();
		if (objects[i]->isDestroyed()) {
			objects.erase(objects.begin() + i);
			i--;
		}
	}
}

template<typename T>
void drawObjects(std::vector<std::shared_ptr<T>>& objects) {
	for (size_t i = 0; i < objects.size(); i++) {
		objects[i]->draw();
	}
}