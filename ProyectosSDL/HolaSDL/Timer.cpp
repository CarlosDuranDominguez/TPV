#include"Timer.h"
#include<math.h>

Timer::Timer(float x, float y, int width, int height, SDL_Color color, Font* font) {
	text = new Text(font, x, y, width, height, color, "0");
	time(&firstTime); time(&currentTime);
};

Timer::Timer(Vector2D position, int width, int height, SDL_Color color, Font* font) {
	text = new Text(font, position, width, height, color, "0");
	time(&firstTime); time(&currentTime);
};

Timer::~Timer() {
	delete text;
}

void Timer::render() const {
	text->setText(to_string((int)getTime()));
	text->render();
}

void Timer::update() {
	time(&currentTime);
}

void Timer::reset() {
	time(&firstTime);
}

double Timer::getTime() const {
	return difftime(currentTime, firstTime);
}