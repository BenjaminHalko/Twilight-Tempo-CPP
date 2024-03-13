#include "global.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "enemy.h"

sf::RenderWindow Global::window;
sf::RenderTexture Global::render;
std::vector<Sound*> Global::sounds;
Player Global::player = Player(0, 0);
std::vector<Bullet*> Global::bullets;
std::vector<Enemy*> Global::enemies;
std::vector<ScorePopup*> Global::scorePopups;
float Global::time_running = 0;
int Global::score = 0;
int Global::highScore = 0;
int Global::lives = 12;
bool Global::practiceMode = false;
bool Global::inTutorial = false;
bool Global::hardMode = false;
bool Global::newGame = true;
float Global::beatTime = 0;