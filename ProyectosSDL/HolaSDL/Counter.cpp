#include "Counter.h"
#include <math.h>

/**
 * Constructors.
 */
Counter::Counter(float x, float y, int width, int height, SDL_Color color, Font *font)
	: _score(0)
{
	_text = new Text(font, x, y, width, height, color, to_string(_score));
}

Counter::Counter(Vector2D position, int width, int height, SDL_Color color, Font *font)
	: _score(0)
{
	_text = new Text(font, position, width, height, color, to_string(_score));
}

/**
 * Destructor.
 */
Counter::~Counter() { delete _text; }

/**
 * Set the score of the counter.
 */
int Counter::setScore(const int num)
{
	_text->setText(to_string(num));
	return _score = num;
}

/**
 * Get the score of the counter.
 */
int Counter::getScore() const
{
	return _score;
}

/**
 * Increase the score of the counter.
 */
int Counter::increaseScore(const int num)
{
	_text->setText(to_string(_score += num));
	return _score;
}

/**
 * The text of the score is renderized.
 */
void Counter::render() const
{
	_text->render();
}
