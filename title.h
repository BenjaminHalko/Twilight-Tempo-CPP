#pragma once
#include "star_generator.h"
#include <SFML/Audio.hpp>
class Title {
private:
	static int choice;
	static bool show;
	static int selected;
	static float logoX;
	static float logoY;
	static float bounce;
	static int lastBeat;
	static int timer;
	static int lastInput;
	static bool lastConfirm;
	static const int bpm = 130;
	static sf::Music music;
	static std::vector<std::shared_ptr<Star>> stars;
	static Sprite twilight;
	static Sprite tempo;
public:
	static void init();
	static void goToTitle();
	static void update();
	static void draw();
};