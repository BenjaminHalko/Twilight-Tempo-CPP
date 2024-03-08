#include "background.h"
#include "beat_controller.h"
#include <SFML/Graphics.hpp>
#include "game_controller.h"
#include "global.h"
#include "object.h"
#include "sound.h"
#include <iostream>

void setupWindow() {
	Global::window.create(sf::VideoMode(256, 224), "Twilight Tempo");
	Global::window.setSize(sf::Vector2u(768, 672));
	Global::window.setFramerateLimit(60);
	
	// Set the window icon
	sf::Image icon;
	icon.loadFromFile("sprites/icon.png");
	Global::window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	// Center the window
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Vector2i windowPosition;
	windowPosition.x = (desktop.width - Global::window.getSize().x) / 2;
	windowPosition.y = (desktop.height - Global::window.getSize().y) / 2;
	Global::window.setPosition(windowPosition);
}

int main() {
	// Create the window
	setupWindow();

	// Start Game
	startGame();

	// Main loop
    while (Global::window.isOpen()) {
		sf::Event event;
        while (Global::window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
				Global::window.close();
			}
		}

		// Debug Restart
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			startGame();
		}

		// Check for stopped sounds
		checkSounds();

		// Update the game
		BeatController::update();
		Global::player.update();


		// Draw the game
		Background::draw();
		Global::player.draw();
		Global::window.display();
	}
   
    return 0;
}