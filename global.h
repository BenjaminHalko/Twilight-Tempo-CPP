#pragma once
#include "sound.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "shadow.h"
#include "score.h"
#include <SFML/Graphics.hpp>
#include <vector>
class Global {
public:
	static const int RESW = 256;
	static const int RESH = 224;
	static float time_running;

	static sf::RenderWindow window;
	static sf::RenderTexture render;
	static std::vector<Sound*> sounds;
	static Player player;
	static std::vector<Bullet*> bullets;
	static std::vector<Enemy*> enemies;
	static std::vector<Score*> scoreObjects;
	
	static float beatTime;
	static int lives;
	static int score;
	static int highScore;
	static bool practiceMode;
	static bool inTutorial;
	static bool hardMode;
	static bool newGame;

};
