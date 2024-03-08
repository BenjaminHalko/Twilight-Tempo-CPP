#include "global.h"
#include <SFML/Graphics.hpp>
#include <vector>

sf::RenderWindow Global::window;
std::vector<Sound*> Global::sounds;
Player Global::player = Player(0,0);
int Global::score = 0;
int Global::lives = 12;
bool Global::inTutorial = false;
bool Global::hardMode = false;
bool Global::newGame = true;
