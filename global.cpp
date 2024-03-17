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
Player Global::player(Global::RESW / 2.0f, Global::RESH / 2.0f);

float Global::time_running = 0;
bool Global::fullscreen = false;
int Global::score = 0;
int Global::highScore = 0;
int Global::lives = 12;
bool Global::practiceMode = false;
bool Global::startInTutorial = true;
bool Global::inTutorial = false;
bool Global::hardMode = false;
bool Global::inTitle = true;
float Global::beatTime = 0;
