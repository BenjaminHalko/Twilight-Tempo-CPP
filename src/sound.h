#pragma once
#include <SFML/Audio.hpp>
#include <string>
class Sound {
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
public:
	Sound(const std::string& filename, int volume);
	~Sound();
	sf::Sound& getSound();
	bool isPlaying();
};
sf::Sound& playSound(const std::string& filename, int volume);
void checkSounds();