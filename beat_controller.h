#pragma once
#include <SFML/Audio.hpp>
class BeatController {
private:
	static sf::Music music;
	static int BPM;
	static int lastBeat;
	static int aheadLastBeat;
	static int beats[8];
	static int mode;
	static const std::string dirSounds[4];
public:
	static const float aheadTime;
	static const int BEAT_COUNT = 8;
	~BeatController();
	static void resetSong();
	static void update();
	static void setTrackPos(float pos);
	static int getBPM();
	static void stopMusic();
};