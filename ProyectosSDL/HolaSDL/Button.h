#pragma once

#include "checkML.h"
#include <functional>
#include "Text.h"

class Button : public Text
{
private:
	SDL_Color _inColor;
	SDL_Color _outColor;
	bool _mouseIn = false;
	function<void()> _callback;

public:
	Button(Font *font, double x, double y, int width, int height, SDL_Color inColor,
				 SDL_Color outColor, string text, function<void()> callback);
	~Button();
	virtual void handleEvents(SDL_Event event);
};
