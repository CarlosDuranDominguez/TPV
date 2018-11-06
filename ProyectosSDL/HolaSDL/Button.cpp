#include "Button.h"

Button::Button(Font *font, double x, double y, int width, int height, SDL_Color inColor, SDL_Color outColor, string text, function<void()> callback)
	: inColor(inColor), outColor(outColor), callback(callback)
{
	this->text = new Text(font, x, y, width, height, outColor, text);
}

Button::~Button()
{
	delete text;
}

void Button::render()
{
	text->render();
}

void Button::handleEvents(SDL_Event event)
{
	SDL_Point p;
	switch (event.type)
	{
	case SDL_MOUSEMOTION:

		p = {event.motion.x, event.motion.y};
		if (SDL_PointInRect(&p, &text->getRect()))
		{
			text->setColor(inColor);
			mouseIn = true;
		}
		else
		{
			text->setColor(outColor);
			mouseIn = false;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (mouseIn && event.button.button == SDL_BUTTON_LEFT)
		{
			callback();
		}
		break;
	default:
		break;
	}
}
