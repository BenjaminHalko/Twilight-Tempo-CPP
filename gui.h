#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "sprite.h"

class GUI {
private:
	static std::vector<Sprite*> hearts;
	static std::vector<float> heartScale;
	static std::vector<float> warningPulse;
public:
	static void init();
	static void clean();
	static void update();
	static void draw();
	static void pulseHeart();
	static void pulseWarning(int i);
};