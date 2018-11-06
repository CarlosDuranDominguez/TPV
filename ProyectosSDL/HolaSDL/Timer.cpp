#include "Timer.h"
#include <math.h>

Timer::Timer(float x, float y, int width, int height, SDL_Color color, Font *font)
{
	_text = new Text(font, x, y, width, height, color, "0");
	time(&_firstTime);
	time(&_currentTime);
};

Timer::Timer(Vector2D position, int width, int height, SDL_Color color, Font *font)
{
	_text = new Text(font, position, width, height, color, "0");
	time(&_firstTime);
	time(&_currentTime);
};

Timer::~Timer()
{
	delete _text;
}

void Timer::render() const
{
	_text->setText(to_string((int)getTime()));
	_text->render();
}

void Timer::update()
{
	time(&_currentTime);
}

void Timer::reset()
{
	time(&_firstTime);
}

double Timer::getTime() const
{
	return difftime(_currentTime, _firstTime);
}
