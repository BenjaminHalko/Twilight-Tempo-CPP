#pragma once
#define PI 3.14159265358979323846
#include <SFML/Graphics.hpp>
sf::Color hexColor(int hex);
float clamp(float value, float min, float max);
float angleDifference(float a, float b);
float approach(float a, float b, float amount);
float approachEase(float value, float target, float maxSpd, float ease);
float approachCircleEase(float value, float target, float maxSpd, float ease);
float point_direction(float x1, float y1, float x2, float y2);
float lengthdir_x(float len, float dir);
float lengthdir_y(float len, float dir);
float random_range(float min, float max);
int irandom(int max);
float lerp(float a, float b, float t);
float wave(float from, float to, float duration, float offset);
float bezierCurve(float t);
void debug(std::string message, float value);
void save(const std::string& fileName, int score);
int load(std::string fileName);
bool fileExists(const std::string& fileName);
