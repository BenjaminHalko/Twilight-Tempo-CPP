#pragma once
#include <SFML/Graphics.hpp>
class Shadow {
private:
	static float darkness;
	static float radius;
public:
	static sf::RenderTexture shadow;
	static const sf::BlendMode blendSubtractive;
	static void init();
	static void update();
	static void draw();
	static void drawCircle(float x, float y, float circleRadius, float alpha);
	static void setDarkness(float dark);
	static void setRadius(float rad);
};
