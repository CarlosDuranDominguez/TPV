#pragma once

#include <time.h>  
#include "Vector2D.h"
#include "Font.h"
#include "Text.h"

class Timer {
private:
	time_t firstTime;
	time_t currentTime;
	Vector2D position;
	int width, height;
	Text* text;
public:
	Timer(float x, float y, int width, int height, SDL_Color color, Font* font);
	Timer(Vector2D position, int width, int height, SDL_Color color, Font* font); 
	~Timer();
	void render();
	void update();
};