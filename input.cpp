#include "input.h"
#include <SFML/Graphics.hpp>

// Manages directional inputs
bool inputLeft() {
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Left) or sf::Keyboard::isKeyPressed(sf::Keyboard::A);
}
bool inputRight() {
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}
bool inputUp() {
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::W);
}
bool inputDown() {
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Down) or sf::Keyboard::isKeyPressed(sf::Keyboard::S);
}
bool inputConfirm() {
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Return) or sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}