// https://github.com/BenjaminHalko/Twilight-Tempo/tree/After-Jam/objects/oTitl
#include "title.h"
#include "global.h"
#include "helper.h"
#include "game_controller.h"
#include "input.h"

int Title::lastBeat = 100;
int Title::choice = 0;
bool Title::show = false;
int Title::selected = 0;
float Title::logoX = 0;
float Title::logoY = 0;
float Title::bounce = 0;
int Title::timer = 0;
int Title::lastInput = 0;
bool Title::lastConfirm = false;
sf::Music Title::music;
std::vector<std::shared_ptr<Star>>Title::stars;
Sprite Title::twilight;
Sprite Title::tempo;

void Title::init() {
	twilight = Sprite("title/twilight.png", 0.5f, 0.5f);
	tempo = Sprite("title/tempo.png");

	Global::startInTutorial = (bool)!load("skipTutorial");

	goToTitle();
}

void Title::goToTitle() {
	lastBeat = 100;
	choice = 0;
	show = false;
	selected = 0;
	logoX = 0;
	logoY = 0;
	bounce = 0;
	stars.clear();
	Global::inTitle = true;
}

void Title::update() {
	if (music.getStatus() == sf::Music::Playing) {
		int _time = (int)floor(music.getPlayingOffset().asSeconds()/60.0f*bpm);
		if (_time != lastBeat)
			bounce = 1.2f;
		lastBeat = _time;
	}

	bounce = approachEase(bounce, 1, 0.05f, 0.6f);

	if (show && selected == 0) {
		bool confirm = false;
		if (inputConfirm()) {
			if (!lastConfirm) {
				confirm = true;
				lastConfirm = true;
			}
		}
		else
			lastConfirm = false;

		if (confirm) {
			if (choice == 2) {
				Global::practiceMode = !Global::practiceMode;
				playSound("blip.ogg", 100);
			}
			else if (choice == 3) {
				Global::startInTutorial = !Global::startInTutorial;
				playSound("blip.ogg", 100);
				save("skipTutorial", (int)!Global::startInTutorial);
			}
			else {
				Global::hardMode = choice;
				selected = 1;
				timer = 5;
				music.stop();
				playSound("select.wav", 30);
			}
		}

		int input = (inputDown() || inputRight()) - (inputUp() || inputLeft());
		if (input != lastInput)
			lastInput = input;
		else
			input = 0;

		if (input == -1) {
			choice--;
			if (choice < 0)
				choice = 3;
			playSound("blip.ogg", 100);
		}
		else if (input == 1) {
			choice++;
			if (choice > 3)
				choice = 0;
			playSound("blip.ogg", 100);
		}
	}
	else if (show) {
		if (--timer <= 0) {
			if (selected == 16) {
				Global::inTitle = false;
				Global::highScore = load(Global::hardMode ? "hard.sav" : "normal.sav");
				Global::inTutorial = Global::startInTutorial;
				startGame();
			}
			selected++;
			timer = 5;
		}
	}

	if (logoY == 0) {
		playSound("intro.wav", 40);
	}

	logoY = approachEase(logoY, 1, 0.015f, 0.85f);

	if (logoY >= 0.9999f) {
		logoY = 1;
		if (logoX == 0)
			playSound("intro2.ogg", 100);
		logoX = approach(logoX, 2, 0.05f);
	}

	if (logoX >= 2 && !show) {
		show = true;
		music.openFromFile("music/song.ogg");
		music.setLoop(true);
		music.play();
	}

	if (stars.size() < 150) {
		std::shared_ptr<Star> s = std::make_unique<Star>();
		s->alpha1 = random_range(0, 1);
		s->alpha2 = random_range(0, 1);
		s->alphaSpd = random_range(1, 5);
		s->alphaOffset = random_range(0, 1);
		s->far = random_range(0, 1);
		stars.push_back(s);
	}

	for (size_t i = 0; i < stars.size(); i++) {
		Star &s = *stars[i];
		s.x -= s.far * 5 * logoX;
		if (s.x < 0) {
			s.x += Global::RESW;
			s.y = (float)fmod(rand(), Global::RESH);
		}
	}
}

void Title::draw() {
	Global::render.clear(sf::Color::Black);
	for (size_t i = 0; i < stars.size(); i++) {
		Star &s = *stars[i];
		sf::Color c = s.color;
		c.a = (sf::Uint8)(wave(s.alpha1, s.alpha2, s.alphaSpd, s.alphaOffset) * 255.0f);
		sf::RectangleShape rect(sf::Vector2f(1, 1));
		rect.setPosition(s.x, s.y);
		rect.setFillColor(c);
		Global::render.draw(rect);
	}

	if (show) {
		drawText(">", 57, 120 + 15 * choice + 10 * (choice >= 2));
		if (choice == 1 || selected % 2 == 0)
			drawText("NORMAL", 72, 120);
		if (choice == 0 || selected % 2 == 0)
			drawText("HARD", 72, 135);
		drawText("PRACTICE: " + (std::string)(Global::practiceMode ? "ON" : "OFF"), 72, 160);
		drawText("SKIP TUTORIAL: " + (std::string)(Global::startInTutorial ? "NO" : "YES"), 72, 175);
		drawText("© 2024 BENJAMIN & KOBE", (int)Global::RESW / 2, 200, true);
		drawText("ALL RIGHTS RESERVED", (int)Global::RESW / 2, 210, true);
	}

	sf::Sprite twi = twilight();
	twi.setPosition(Global::RESW / 2.0f, lerp(100, 40, logoY));
	twi.setScale(lerp(1.5f, 1, logoY) * bounce, bounce);
	twi.setColor(sf::Color(255, 255, 255, (sf::Uint8)(255.0f * logoY)));
	Global::render.draw(twi);

	sf::Sprite tem = tempo();
	tem.setPosition(Global::RESW / 2.0f - 10, 50);
	if (logoX < 1)
		tem.setTextureRect(sf::IntRect(0, 0, (int)(tempo.getWidth() * logoX), tempo.getHeight()));
	Global::render.draw(tem);
}
