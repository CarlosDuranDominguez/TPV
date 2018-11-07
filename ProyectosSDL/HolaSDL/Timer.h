#pragma once

#include "checkML.h"
#include <time.h>
#include "Vector2D.h"
#include "Font.h"
#include "Text.h"

class Timer
{
private:
	time_t _firstTime;
	time_t _currentTime;
	Vector2D _position;
	int _width, _height;
	Text *_text;

public:
	Timer(float x, float y, int width, int height, SDL_Color color, Font *font);
	Timer(Vector2D position, int width, int height, SDL_Color color, Font *font);
	~Timer();
	void render() const;
	void update();
	void reset();
	double getTime() const;
};
