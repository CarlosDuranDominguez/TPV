#include "Button.h"

/*
 * Constructor.
 */
Button::Button(Font *font, double x, double y, int width, int height, SDL_Color inColor, SDL_Color outColor, string text, function<void()> callback)
	: _inColor(inColor), _outColor(outColor), _callback(callback)
{
	this->_text = new Text(font, x, y, width, height, outColor, text);
}

/*
 * Destructor.
 */
Button::~Button()
{
	delete _text;
}

/*
 * Button's text is renderized in the correct position.
 */
void Button::render() const
{
	_text->render();
}

/*
 * It detects if the cursor is on the button. If it is clicked the call the callback function.
 */
void Button::handleEvents(SDL_Event event)
{
	SDL_Point p;
	switch (event.type)
	{
	case SDL_MOUSEMOTION:

		p = {event.motion.x, event.motion.y};
		if (SDL_PointInRect(&p, &_text->getRect()))
		{
			_text->setColor(_inColor);
			_mouseIn = true;
		}
		else
		{
			_text->setColor(_outColor);
			_mouseIn = false;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (_mouseIn && event.button.button == SDL_BUTTON_LEFT)
		{
			_callback();
		}
		break;
	default:
		break;
	}
}
