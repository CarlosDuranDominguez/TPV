#pragma once

#include "Text.h"
#include <functional>

class Button
{
private:
	Text *text;
	SDL_Color inColor;
	SDL_Color outColor;
	bool mouseIn = false;
	function<void()> callback;

public:
	Button(Font *font, double x, double y, int width, int height, SDL_Color inColor, SDL_Color outColor, string text, function<void()> callback);
	~Button();
	void render();
	void handleEvents(SDL_Event event);
};
