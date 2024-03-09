// https://github.com/BenjaminHalko/Twilight-Tempo/tree/After-Jam/objects/oBeatController
#include "beat_controller.h"
#include "global.h"
#include "sound.h"
#include "helper.h"
#include "enemy.h"
#include <SFML/Audio.hpp>
#include <string>

sf::Music BeatController::music;
int BeatController::BPM = 130;
int BeatController::lastBeat = 100;
int BeatController::aheadLastBeat = 100;
int BeatController::beats[BEAT_COUNT] = {4,4,4,4,4,4,4,4};
int BeatController::mode = 0;
const std::string BeatController::dirSounds[4] = {"left.ogg", "up.ogg", "right.ogg", "down.ogg"};
const float BeatController::aheadTime = 0.73f;

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
	return BPM;
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
		Global::beatTime = (float)(musicPos / 60.0) * BPM;
		int beat = (int)Global::beatTime % BEAT_COUNT * 2;
		int aheadBeat = (int)(Global::beatTime + aheadTime) % BEAT_COUNT * 2;

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



		if (aheadBeat != aheadLastBeat && aheadBeat >= BEAT_COUNT && beats[aheadBeat-BEAT_COUNT] != 4) {
			int _dir = beats[aheadBeat-BEAT_COUNT] * 90;
			Global::enemies.push_back(new Enemy(Global::RESW / 2 + lengthdir_x(150, (float)_dir), Global::RESH / 2 + lengthdir_y(150, (float)_dir), (float)_dir));
		}

		lastBeat = beat;
		aheadLastBeat = aheadBeat;
	}
}