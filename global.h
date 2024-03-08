#pragma once
#include "sound.h"
#include "player.h"
#include <SFML/Graphics.hpp>
#include <vector>
class Global {
public:
	static const int RESW = 256;
	static const int RESH = 224;

	static sf::RenderWindow window;
	static std::vector<Sound*> sounds;
	static Player player;

	static int lives;
	static int score;
	static bool inTutorial;
	static bool hardMode;
	static bool newGame;
};
