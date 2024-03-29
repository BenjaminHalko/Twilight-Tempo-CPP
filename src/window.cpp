#include <cmath>
#include <SFML/Graphics.hpp>
#include "window.h"
#include "global.h"

// Function to create the game window
void createWindow() {
	// Create and resize windows
	Global::window.create(sf::VideoMode(Global::RESW * Global::WINDOW_SCALE, Global::RESH * Global::WINDOW_SCALE), "Twilight Tempo", Global::fullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	Global::window.setFramerateLimit(60);
	Global::window.setMouseCursorVisible(false);

	// Set the window icon
	sf::Image icon;
	icon.loadFromFile("resources/sprites/icon/icon.png");
	Global::window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	// Set the window size
	if (!Global::fullscreen) {
		sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
		sf::Vector2i windowPosition;
		windowPosition.x = (int)(desktop.width - Global::window.getSize().x) / 2;
		windowPosition.y = (int)(desktop.height - Global::window.getSize().y) / 2;
		Global::window.setPosition(windowPosition);
		Global::window.clear(sf::Color::Black);
	}
}

void toggleFullscreen() {
	Global::fullscreen = !Global::fullscreen;
	Global::window.close();
	createWindow();
}

void renderWindow() {
	sf::Sprite renderSprite(Global::render.getTexture());
	if (Global::fullscreen) {
		sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
		auto scale = (float)std::fmin((float)desktop.width / Global::RESW, (float)desktop.height / Global::RESH);
		renderSprite.setScale(scale, -scale);
		renderSprite.setPosition(((float)desktop.width - Global::RESW * scale) / 2, ((float)desktop.height + Global::RESH * scale) / 2);
	}
	else {
		renderSprite.setPosition(0, Global::RESH * Global::WINDOW_SCALE);
		renderSprite.setScale(Global::WINDOW_SCALE, -Global::WINDOW_SCALE);
	}
	Global::window.draw(renderSprite);
	Global::window.display();
}
