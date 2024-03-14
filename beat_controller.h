#pragma once
#include <SFML/Audio.hpp>
class BeatController {
private:
	static sf::Music music;
	static int BPM;
	static int lastBeat;
	static int aheadLastBeat;
	static std::vector<int> beats;
	static std::vector<int> extraBeats;
	static float mode;
	static const std::string dirSounds[4];
	static int barNumber;
public:
	static const float aheadTime;
	static const int BEAT_COUNT = 8;
	~BeatController();
	static void resetSong();
	static void update();
	static void setTrackPos(float pos);
	static int getBarNumber();
	static int getBPM();
	static void stopMusic();
};