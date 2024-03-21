#include "helper.h"
#include "global.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <fstream>
#include <cstdlib>

// Converts hexColor to SFML color
sf::Color hexColor(int hex) {
	int r = (hex >> 16) & 0xFF;
	int g = (hex >> 8) & 0xFF;
	int b = hex & 0xFF;
	return sf::Color(r, g, b);
}

// Clamp between two values
float clamp(float value, float min, float max) {
	if (value < min) {
		return min;
	}
	if (value > max) {
		return max;
	}
	return value;
}

// Get's the difference between two angles
float angleDifference(float a, float b) {
	float difference = (float)fmod(b - a + 180, 360) - 180;
	if (difference < -180) {
		difference += 360;
	}
	return difference;
}

// Move towards value a to move towards b at speed of amount 
float approach(float a, float b, float amount) {
	if (a < b) {
		a += amount;
		if (a > b) {
			return b;
		}
	}
	else {
		a -= amount;
		if (a < b) {
			return b;
		}
	}
	return a;
}

float approachEase(float value, float target, float maxSpd, float ease) {
	value += clamp((1 - ease) * (target - value), -maxSpd, maxSpd);
	return value;
}

float approachCircleEase(float value, float target, float maxSpd, float ease) {
	value += clamp((1 - ease) * angleDifference(value, target), -maxSpd, maxSpd);
	return value;
}

// Returns the direction when given two points
float point_direction(float x1, float y1, float x2, float y2) {
	return (float)(std::atan2(y2 - y1, x2 - x1) * 180 / PI);
}

// Returns the distance when given two points
float point_distance(float x1, float y1, float x2, float y2) {
	return (float)sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Given a length and direction, return x component
float lengthdir_x(float len, float dir) {
	return (float)cos(dir * PI / 180) * len;
}	

// Given a length and direction, return x component
float lengthdir_y(float len, float dir) {
	return (float)sin(dir * PI / 180) * len;
}

// Returns a random number between min and max
float random_range(float min, float max) {
	return min + (max - min) * (float)rand() / RAND_MAX;
}

// Gives a random number between 0 and max
int irandom(int max) {
	return rand() % max;
}

// Performs linear interpolation between two floats, in reference to t, time
float lerp(float a, float b, float t) {
	return a + (b - a) * t;
}

// Waves between two values
float wave(float from, float to, float duration, float offset) {
	float a4 = (to - from) * 0.5f;
	return (float)(from + a4 + a4 * sin((float)(Global::time_running + duration * offset) / duration * 2 * PI));
}

// Idk man that's Benjamins thing
float bezierCurve(float t) {
	float y2 = 0;
	float y3 = 1.461f;
	float y4 = 1;

	float p1y1 = 0;
	float p1y2 = lerp(y2, y3, t);
	float p1y3 = lerp(y3, y4, t);

	float p2y1 = lerp(p1y1, p1y2, t);
	float p2y2 = lerp(p1y2, p1y3, t);

	float p3y = lerp(p2y1, p2y2, t);

	return p3y;
}

bool fileExists(const std::string& fileName) {
	// Returns false if file doesn't exist/can't be opened
	std::ifstream file(fileName);
	return file.good();
}

void save(std::string fileName, int score) {
	fileName = fileName + ".sav";
	std::ofstream outFile(fileName, std::ios::trunc);
	outFile << score;
	outFile.close();
}

int load(std::string fileName) {
	fileName = fileName + ".sav";
	int score;
	std::ifstream inFile;
	if (fileExists(fileName)) {
		inFile.open(fileName);
		if (inFile >> score) {
			return score;
		}
	}
	return 0;
}

std::string formatScore(int score, int stringLength) {
	std::string formattedScore = std::to_string(score);
	if ((int)formattedScore.length() >= stringLength) {
		return formattedScore;
	}
	else {
		formattedScore = std::string(stringLength - formattedScore.length(), '0') + formattedScore;
		return formattedScore;
	}
}

void drawText(sf::String textString, int x, int y, bool horizCentered, bool vertCentered, bool useM3x6, sf::Color colour, int scale) {
	sf::Text text;
	text.setFont(useM3x6 ? Global::m3x6 : Global::pressStart);
	text.setString(textString);
	text.setCharacterSize((useM3x6 ? 16 : 8) * scale);
	text.setPosition(std::floor((float)x - ((float)horizCentered * (text.getGlobalBounds().width / 2))), std::floor((float)y - ((float)vertCentered * (text.getGlobalBounds().height / 2))));
	text.setFillColor(colour); // Set the fill color

	Global::render.draw(text);
}
