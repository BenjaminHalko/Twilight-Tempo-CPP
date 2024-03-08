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
	float difference = (float)fmod(b - a + 180, 360) - 180;
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
	return (float)(atan2(y2 - y1, x2 - x1) * 180 / PI);
}

float lengthdir_x(float len, float dir) {
	return (float)cos(dir * PI / 180) * len;
}	

float lengthdir_y(float len, float dir) {
	return (float)sin(dir * PI / 180) * len;
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