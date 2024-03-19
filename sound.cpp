#include "sound.h"
#include "global.h"
#include <SFML/Audio.hpp>

sf::Sound& playSound(std::string filename, int volume) {
	std::shared_ptr<Sound> s = std::make_shared<Sound>(filename, volume);
	Global::sounds.push_back(s);
	return s->getSound();
}

void checkSounds() {
	for (size_t i = 0; i < Global::sounds.size(); i++) {
		if (!Global::sounds[i]->isPlaying()) {
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

sf::Sound& Sound::getSound() {
	return sound;
}

bool Sound::isPlaying() {
	return sound.getStatus() == sf::Sound::Playing;
}

Sound::~Sound() {
	sound.stop();
}
