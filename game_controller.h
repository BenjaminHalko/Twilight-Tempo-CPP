#pragma once
#include "bullet.h"
#include "enemy.h"
void startGame();
void updateObjects(std::vector<Bullet*>& objects);
void updateObjects(std::vector<Enemy*>& objects);
void drawObjects(std::vector<Bullet*>& objects);
void drawObjects(std::vector<Enemy*>& objects);