#include "helper.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <iostream>

sf::Color hexColor(int hex) {
	int r = (hex >> 16) & 0xFF;
	int g = (hex >> 8) & 0xFF;
	int b = hex & 0xFF;
	return sf::Color(r, g, b);
}

float clamp(float value, float min, float max) {
	if (value < min) {
		return min;
	}
	if (value > max) {
		return max;
	}
	return value;
}

float angleDifference(float a, float b) {
	float difference = fmod(b - a + 180, 360) - 180;
	if (difference < -180) {
		difference += 360;
	}
	return difference;
}

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

float point_direction(float x1, float y1, float x2, float y2) {
	return atan2(y2 - y1, x2 - x1) * 180 / PI;
}

float lengthdir_x(float len, float dir) {
	return cos(dir * PI / 180) * len;
}	

float lengthdir_y(float len, float dir) {
	return sin(dir * PI / 180) * len;
}

float random_range(float min, float max) {
	return min + (max - min) * (float)rand() / RAND_MAX;
}

int irandom(int max) {
	return rand() % max;
}

float lerp(float a, float b, float t) {
	return a + (b - a) * t;
}

void debug(std::string message, float value) {
	std::cout << message << ": " << value << std::endl;
}