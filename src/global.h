#pragma once
#include "sound.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "score_popup.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
class Global {
public:
	static const int RESW = 256;
	static const int RESH = 224;
	static const int WINDOW_SCALE = 3;
	static float time_running;

	static sf::Font pressStart;
	static sf::Font m3x6;

	static sf::RenderWindow window;
	static sf::RenderTexture render;
	static bool fullscreen;

	static std::vector<std::shared_ptr<Sound>> sounds;
	static std::vector<std::shared_ptr<Bullet>> bullets;
	static std::vector<std::shared_ptr<Enemy>> enemies;
	static std::vector<std::shared_ptr<ScorePopup>> scorePopups;
	static Player player;
	
	static float beatTime;
	static int lives;
	static int score;
	static int highScore;
	static bool practiceMode;
	static bool startInTutorial;
	static bool inTutorial;
	static bool hardMode;
	static bool inTitle;
};
