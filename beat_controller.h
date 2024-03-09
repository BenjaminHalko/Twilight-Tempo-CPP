#pragma once
#include <SFML/Audio.hpp>
class BeatController {
private:
	static sf::Music music;
	static const int BEAT_COUNT = 8;
	static int BPM;
	static int lastBeat;
	static int aheadLastBeat;
	static int beats[BEAT_COUNT];
	static int mode;
	static const std::string dirSounds[4];
public:
	~BeatController();
	static void resetSong();
	static void update();
	static void setTrackPos(float pos);
	static int getBPM();
	static void stopMusic();
};