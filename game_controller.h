#pragma once
#include "bullet.h"
#include "enemy.h"
#include "score.h"
void startGame();
void updateObjects(std::vector<Bullet*>& objects);
void updateObjects(std::vector<Enemy*>& objects);
void updateObjects(std::vector<Score*>& objects);
void drawObjects(std::vector<Score*>& objects);
void drawObjects(std::vector<Bullet*>& objects);
void drawObjects(std::vector<Enemy*>& objects);
void cleanUp();