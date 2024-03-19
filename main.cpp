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
#include "title.h"
#include "window.h"

int main() {
	// Create the window
	Global::render.create(Global::RESW, Global::RESH);
	createWindow();

	// Load the fonts
	Global::m3x6.loadFromFile("fonts/m3x6.ttf");
	Global::pressStart.loadFromFile("fonts/press_start.ttf");

	// Init objects
	Shadow::init();
	GUI::init();
	StarGenerator::init();
	Title::init();

	// Check for fullscreen
	bool holdingFullscreen = false;

	// Main loop
	while (Global::window.isOpen()) {
		// Event handling
		sf::Event event{};
		while (Global::window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				Global::window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4) || sf::Keyboard::isKeyPressed(sf::Keyboard::F11)) {
			if (!holdingFullscreen) {
				toggleFullscreen();
				holdingFullscreen = true;
			}
		}
		else {
			holdingFullscreen = false;
		}

		// Check for stopped sounds
		checkSounds();
		
		if (Global::inTitle) {
			// Title
			Title::update();
			Title::draw();
		} else {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				BeatController::stopMusic();
				Title::goToTitle();
				continue;
			}

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
			drawObjects(Global::bullets);
			drawObjects(Global::enemies);
			drawObjects(Global::scorePopups);
			Shadow::draw();
			Global::player.draw();
			GUI::draw();
		}

		// Draw the window
		renderWindow();

		// Update the time
		Global::time_running += 1.0f / 60.0f;
	}

    return 0;
}
