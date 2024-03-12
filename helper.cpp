#include "helper.h"
#include "global.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>


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
	return (float)(atan2(y2 - y1, x2 - x1) * 180 / PI);
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

// Can output debug message
void debug(std::string message, float value) {
	std::cout << message << ": " << value << std::endl;
}

// Idk man that's Benjamins thing
float bezierCurve(float t) {
	float x1 = 0;
	float y1 = 0;
	float x2 = 0.3f;
	float y2 = 0;
	float x3 = 0.318f;
	float y3 = 1.461f;
	float x4 = 1;
	float y4 = 1;

	float p1x1 = lerp(x1, x2, t);
	float p1y1 = lerp(y1, y2, t);
	float p1x2 = lerp(x2, x3, t);
	float p1y2 = lerp(y2, y3, t);
	float p1x3 = lerp(x3, x4, t);
	float p1y3 = lerp(y3, y4, t);

	float p2x1 = lerp(p1x1, p1x2, t);
	float p2y1 = lerp(p1y1, p1y2, t);
	float p2x2 = lerp(p1x2, p1x3, t);
	float p2y2 = lerp(p1y2, p1y3, t);

	float p3x = lerp(p2x1, p2x2, t);
	float p3y = lerp(p2y1, p2y2, t);

	return p3y;
}

void save(const std::string& fileName, int score) {
	std::ofstream outFile(fileName + ".sav", std::ios::trunc);
	if(!outFile.is_open()){
		std::cerr << "Error opening file: " << fileName << ".sav" << std::endl;
		return;
	}
	outFile << score;
	outFile.close();
}

int load(std::string fileName) {
	int score;
	std::ifstream inFile;

	if (fileExists(fileName + ".sav")) {
		inFile.open(fileName + ".sav");
		if (inFile >> score) {
			return score;
		}
	}

	std::cerr << "Error: File " << fileName << ".sav does not exist." << std::endl;
	return -1;
}

bool fileExists(const std::string& fileName) {
	// Returns false if file doesn't exist/can't be opened
	std::ifstream file(fileName);
	return file.good();
}

std::string formatScore(int score, int stringLength) {
	std::string formattedScore = std::to_string(score);
	formattedScore = std::string(stringLength - formattedScore.length(), '0') + formattedScore;
	return formattedScore;
}