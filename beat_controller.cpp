// https://github.com/BenjaminHalko/Twilight-Tempo/tree/After-Jam/objects/oBeatController
#include "beat_controller.h"
#include "global.h"
#include "sound.h"
#include "helper.h"
#include "enemy.h"
#include "shadow.h"
#include "gui.h"
#include <SFML/Audio.hpp>
#include <string>

sf::Music BeatController::music;
int BeatController::BPM = 130;
int BeatController::lastBeat = 100;
int BeatController::aheadLastBeat = 100;
std::vector<int> BeatController::beats(8, 4);
std::vector<int> BeatController::extraBeats(4, 0);
float BeatController::mode = 0;
const std::string BeatController::dirSounds[4] = {"left.ogg", "up.ogg", "right.ogg", "down.ogg"};
const float BeatController::aheadTime = 0.73f;
int BeatController::barNumber = 0;

void BeatController::resetSong() {
	barNumber = 0;
	mode = 0;
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

int BeatController::getBarNumber() {
	return barNumber;
}

int BeatController::getBPM() {
	return BPM;
}

void BeatController::stopMusic() {
	music.stop();
}

void BeatController::update() {
	if (Global::lives <= 0) {
		music.stop();
		return;
	}

	if (music.getStatus() == sf::Music::Playing) {
		double musicPos = music.getPlayingOffset().asSeconds();
		if (musicPos < 0) {
			musicPos += music.getDuration().asSeconds();
		}
		Global::beatTime = (float)(musicPos / 60.0) * BPM;
		int beat = (int)Global::beatTime % BEAT_COUNT * 2;
		int aheadBeat = (int)(Global::beatTime + aheadTime) % BEAT_COUNT * 2;

		if (beat < lastBeat) {
			if (Global::score >= 40000) {
				if (mode != 9) {
					extraBeats.assign({0, 0, 4, 8});
				} mode = 9;
			}
			else if (Global::score >= 35000) {
				if (mode != 8) {
					extraBeats.assign({ 0, 0, 8, 8 });
				} mode = 8;
			}
			else if (Global::score >= 30000) {
				if (mode != 7) {
					extraBeats.assign({ 0, 1, 8, 12 });
				} mode = 7;
			}
			else if (Global::score >= 20000) {
				if (mode != 6) {
					extraBeats.assign({ 0, 1, 8, 16 });
				} mode = 6;
			}
			else if (Global::score >= 15000) {
				if (mode != 5) {
					extraBeats.assign({ 0, 1, 10, 18 });
				} mode = 5;
			}
			else if (Global::score >= 10000) {
				if (mode != 4) {
					extraBeats.assign({ 0, 6, 12, 24 });
				} mode = 4;
			}
			else if (Global::score >= 5000) {
				if (mode != 3) {
					extraBeats.assign({ 1, 6, 12, 24 });
				} mode = 3;
			}
			else if (Global::score >= 3000) {
				if (mode < 2) {
					extraBeats.assign({ -6, -1, -1, -1 });
					mode = 2;
				}
			}
			else if (Global::score >= 600) {
				mode = 1;
			}

			if (Global::inTutorial || mode >= 3) {
				barNumber++;
			}

			if (barNumber == 9 && Global::inTutorial) {
				music.stop();
				return;
			}
			else if (barNumber == 8 && Global::inTutorial) {
				beats = { 2, 4, 3, 4, 0, 4, 1, 4 };
			}
			else {
				for (int i = 0; i < 4; i++) {
					int j = irandom(4);
					int temp = extraBeats[i];
					extraBeats[i] = extraBeats[j];
					extraBeats[j] = temp;
				}
				for (int i = 0; i < BEAT_COUNT; i++) {
					if (i % 2 == 1) {
						if (!Global::inTutorial && mode > 1 && extraBeats[i / 2] != -1 && (irandom(1+(int)fmax(0, 8-barNumber)+extraBeats[i / 2]) == 0 || mode == 2)) {
							beats[i] = irandom(4);
						}
						else {
							beats[i] = 4;
						}
					}
					else if (!Global::inTutorial && i % 4 == 2 && mode == 0) {
						beats[i] = beats[i - 2];
					}
					else {
						beats[i] = irandom(4);
					}
				}
			}

			if (mode == 2) {
				mode = 2.5;
			}
		}

		if (beat != lastBeat) {
			if (beat % 2 == 0) {
				Global::player->setCannonMove(2);
				if (!Global::inTutorial)
					Shadow::setRadius(1);
			}
			if (beat < BEAT_COUNT) {
				if (beats[beat] != 4) {
					int dir = beats[beat] * 90;
					if (Global::inTutorial || Global::practiceMode)
						GUI::pulseWarning(beats[beat]);
					playSound(dirSounds[beats[beat]], 100);
				}
			}
		}

		if (aheadBeat != aheadLastBeat && aheadBeat >= BEAT_COUNT && beats[aheadBeat-BEAT_COUNT] != 4) {
			int _dir = 180 + beats[aheadBeat-BEAT_COUNT] * 90;
			Global::enemies.push_back(std::make_unique<Enemy>(Global::RESW / 2 + lengthdir_x(150, (float)_dir), Global::RESH / 2 + lengthdir_y(150, (float)_dir), (float)_dir));
		}

		lastBeat = beat;
		aheadLastBeat = aheadBeat;
	}
	else if (Global::inTutorial && music.getStatus() != sf::Music::Playing && barNumber != 0) {
		barNumber = 9;
	}
}