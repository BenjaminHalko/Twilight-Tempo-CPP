#include "sound.h"
#include "global.h"
#include <SFML/Audio.hpp>
#include <iostream>

Sound& playSound(std::string filename, int volume) {
	Sound *s = new Sound(filename, volume);
	Global::sounds.push_back(s);
	return *s;
}

void checkSounds() {
	for (int i = 0; i < (signed)Global::sounds.size(); i++) {
		if (!Global::sounds[i]->isPlaying()) {
			delete Global::sounds[i];
			Global::sounds.erase(Global::sounds.begin() + i);
		}
	}
}

Sound::Sound(std::string filename, int volume) {
	buffer.loadFromFile("sounds/" + filename);
	sound.setBuffer(buffer);
	sound.setVolume((float)volume);
	sound.play();
}

sf::Sound& Sound::operator()() {
	return sound;
}

bool Sound::isPlaying() {
	return sound.getStatus() == sf::Sound::Playing;
}

Sound::~Sound() {
	sound.stop();
}
