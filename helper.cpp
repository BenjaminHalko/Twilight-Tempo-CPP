#include "helper.h"
#include <SFML/Graphics.hpp>
#include <string>

sf::Color hexColor(int hex) {
	int r = (hex >> 16) & 0xFF;
	int g = (hex >> 8) & 0xFF;
	int b = hex & 0xFF;
	return sf::Color(r, g, b);
}