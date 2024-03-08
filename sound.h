#pragma once
#include <SFML/Audio.hpp>
#include <string>
class Sound {
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
public:
	Sound(std::string filename, int volume);
	sf::Sound& operator()();
	bool isPlaying();
};
Sound& playSound(std::string filename, int volume);
void checkSounds();