#include "beat_controller.h"
#include "global.h"
#include "sound.h"
#include "helper.h"
#include <SFML/Audio.hpp>
#include <string>

sf::Music BeatController::music;
int BeatController::BPM = 130;
int BeatController::lastBeat = 100;
int BeatController::aheadLastBeat = 100;
int BeatController::beats[BEAT_COUNT] = {4,4,4,4,4,4,4,4};
int BeatController::mode = 0;
const std::string BeatController::dirSounds[4] = {"left.ogg", "up.ogg", "right.ogg", "down.ogg"};

void BeatController::resetSong() {
	music.stop();

	std::string song = "song";
	if (Global::inTutorial) {
		song += "_tutorial";
	}
	if (Global::hardMode) {
		song += "_hard";
	}

	BeatController::BPM = (Global::hardMode) ? 170 : 130;

	music.openFromFile("music/"+song+".ogg");
	music.play();
	music.setLoop(!Global::inTutorial);
}

BeatController::~BeatController() {
	music.stop();
}

void BeatController::setTrackPos(float pos) {
	music.setPlayingOffset(sf::seconds(pos));
}

int BeatController::getBPM() {
	return BeatController::BPM;
}

void BeatController::stopMusic() {
	music.stop();
}

void BeatController::update() {
	if (music.getStatus() == sf::Music::Playing) {
		double musicPos = music.getPlayingOffset().asSeconds();
		if (musicPos < 0) {
			musicPos += music.getDuration().asSeconds();
		}
		double timepos = (musicPos / 60.0) * BPM;
		int beat = (int)timepos % BEAT_COUNT * 2;
		int aheadBeat = (int)(timepos + aheadLastBeat) % BEAT_COUNT * 2;

		if (beat < lastBeat) {
			for (int i = 0; i < BEAT_COUNT; i++) {
				if (i % 2 == 1) {
					// TODO
				}
				else {
					beats[i] = irandom(4);
				}
			}
		}

		if (beat != lastBeat) {
			if (beat % 2 == 0) {
				Global::player.setCannonMove(2);
			}
			if (beat < BEAT_COUNT) {
				if (beats[beat] != 4) {
					int dir = beats[beat] * 90;
					playSound(dirSounds[beats[beat]], 65);
				}
			}
		}

		lastBeat = beat;
		aheadLastBeat = aheadBeat;
	}
}