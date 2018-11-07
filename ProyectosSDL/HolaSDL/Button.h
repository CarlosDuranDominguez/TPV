#pragma once

#include "checkML.h"
#include "Text.h"
#include <functional>

class Button
{
private:
	Text *_text;
	SDL_Color _inColor;
	SDL_Color _outColor;
	bool _mouseIn = false;
	function<void()> _callback;

public:
	Button(Font *font, double x, double y, int width, int height, SDL_Color inColor, SDL_Color outColor, string text, function<void()> callback);
	~Button();
	void render() const;
	void handleEvents(SDL_Event event);
};
