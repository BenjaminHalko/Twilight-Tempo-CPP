#include "background.h"
#include "beat_controller.h"
#include <SFML/Graphics.hpp>
#include "game_controller.h"
#include "global.h"
#include "object.h"
#include "sound.h"
#include "shadow.h"
#include "gui.h"
#include "star_generator.h"

// Function to create the game window
void setupWindow() {
	// Create and resize windows
	Global::window.create(sf::VideoMode(256, 224), "Twilight Tempo");
	Global::render.create(256, 224);
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

	// Load the fonts
	Global::m3x6.loadFromFile("fonts/m3x6.ttf");
	Global::pressStart.loadFromFile("fonts/press_start.ttf");

	// Create the shadow & GUI
	Shadow::init();
	GUI::init();
	StarGenerator::init();

	// Start Game
	startGame();

	// Main loop
    while (Global::window.isOpen()) {
		// Event handling
		sf::Event event;
        while (Global::window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
				Global::window.close();
			}
		}

		// Debug Restart
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			restartGame();
		}

		// Check for stopped sounds
		checkSounds();

		// Update the game
		BeatController::update();
		Background::update();
		Global::player.update();
		updateObjects(Global::bullets);
		updateObjects(Global::enemies);
		updateObjects(Global::scorePopups);
		Shadow::update();
		GUI::update();

		// Draw the game
		StarGenerator::update();
		Background::draw();
		Global::player.draw();
		drawObjects(Global::bullets);
		drawObjects(Global::enemies);
		drawObjects(Global::scorePopups);
		Shadow::draw();
		GUI::draw();

		// Draw the window
		sf::Sprite renderSprite(Global::render.getTexture());
		renderSprite.setPosition(0, Global::RESH);
		renderSprite.setScale(1, -1);
		Global::window.draw(renderSprite);
		Global::window.display();

		// Update the time
		Global::time_running += 1.0f / 60.0f;
	}

	// Clean up
	StarGenerator::deleteStars();
	cleanUp();

    return 0;
}