#pragma once
#include "bullet.h"
#include "enemy.h"
#include "score_popup.h"
void startGame();
void restartGame();
void updateObjects(std::vector<Bullet*>& objects);
void updateObjects(std::vector<Enemy*>& objects);
void updateObjects(std::vector<ScorePopup*>& objects);
void drawObjects(std::vector<ScorePopup*>& objects);
void drawObjects(std::vector<Bullet*>& objects);
void drawObjects(std::vector<Enemy*>& objects);
void cleanUp();