#include "Timer.h"
#include <math.h>

/**
 * Constructors.
 */
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

/**
 * Destructor.
 */
Timer::~Timer()
{
	delete _text;
}

/**
 * It renders the timer text.
 */
void Timer::render() const
{
	_text->setText(to_string((int)getTime()));
	_text->render();
}

/**
 * It updates the current time.
 */
void Timer::update()
{
	time(&_currentTime);
}

/**
 * It resets the timer to zero.
 */
void Timer::reset()
{
	time(&_firstTime);
}

/**
 * It gets the time since the timer was created or reseted.
 */
double Timer::getTime() const
{
	return difftime(_currentTime, _firstTime);
}
