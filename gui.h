#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "sprite.h"

class GUI {
private:
	static std::vector<std::shared_ptr<Sprite>> hearts;
	static std::vector<float> heartScale;
	static std::vector<float> warningPulse;
	static int timer;
	static float gameOverTimer;
	static bool gameOverChoice;
	static int newRecord;
	static bool menuHeldInput;
public:
	static void init();
	static void update();
	static void draw();
	static void pulseHeart();
	static void pulseWarning(int i);
};
