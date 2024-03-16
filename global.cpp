#include "global.h"
#include <SFML/Graphics.hpp>
#include <vector>

sf::RenderWindow Global::window;
sf::RenderTexture Global::render;

sf::Font Global::pressStart;
sf::Font Global::m3x6;

std::vector<std::shared_ptr<Sound>> Global::sounds;
std::vector<std::shared_ptr<Bullet>> Global::bullets;
std::vector<std::shared_ptr<Enemy>> Global::enemies;
std::vector<std::shared_ptr<ScorePopup>> Global::scorePopups;
std::unique_ptr<Player> Global::player;

float Global::time_running = 0;
int Global::score = 0;
int Global::highScore = 0;
int Global::lives = 12;
bool Global::practiceMode = false;
bool Global::inTutorial = false;
bool Global::hardMode = false;
bool Global::inTitle = false;
float Global::beatTime = 0;