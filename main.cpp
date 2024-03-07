#include "background.h"
#include <SFML/Graphics.hpp>

void setupWindow(sf::RenderWindow& window) {
	window.create(sf::VideoMode(256, 224), "Twilight Tempo");
	window.setSize(sf::Vector2u(768, 672));
	window.setFramerateLimit(60);
	
	// Set the window icon
	sf::Image icon;
	icon.loadFromFile("sprites/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	// Center the window
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Vector2i windowPosition;
	windowPosition.x = (desktop.width - window.getSize().x) / 2;
	windowPosition.y = (desktop.height - window.getSize().y) / 2;
	window.setPosition(windowPosition);
}

int main() {
	// Create the window
    sf::RenderWindow window;
	setupWindow(window);

	// Create the background
	Background background;

	// Main loop
    while (window.isOpen()) {
		sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		background.draw(window);
		window.display();
	}
   
    return 0;
}