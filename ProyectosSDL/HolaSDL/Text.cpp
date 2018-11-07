#include "Text.h"

/**
 * Constructors.
 */
Text::Text(Font *font, float x, float y, int width, int height, const SDL_Color &color, const string &text)
	: _font(font), _position(x, y), _width(width), _height(height), _color(color), _text(text)
{
	SDL_Surface *textSurface = TTF_RenderText_Solid(font->getFont(), text.c_str(), color);
	_textTexture = SDL_CreateTextureFromSurface(font->getRenderer(), textSurface);
	SDL_FreeSurface(textSurface);
}

Text::Text(Font *font, const Vector2D &position, int width, int height, const SDL_Color &color, const string &text)
	: _font(font), _position(position), _width(width), _height(height), _color(color), _text(text)
{
	SDL_Surface *textSurface = TTF_RenderText_Solid(font->getFont(), text.c_str(), color);
	_textTexture = SDL_CreateTextureFromSurface(font->getRenderer(), textSurface);
	SDL_FreeSurface(textSurface);
}

/**
 * Destructor.
 */
Text::~Text()
{
	SDL_DestroyTexture(_textTexture);
}

/**
 * It changes the text by newText.
 */
void Text::setText(const string newText)
{
	SDL_DestroyTexture(_textTexture);
	SDL_Surface *textSurface = TTF_RenderText_Solid(_font->getFont(), newText.c_str(), _color);
	_textTexture = SDL_CreateTextureFromSurface(_font->getRenderer(), textSurface);
	SDL_FreeSurface(textSurface);
}

/**
 * It gets the rect of the text.
 */
SDL_Rect Text::getRect() const
{
	return {
		(int)_position.getX(),
		(int)_position.getY(),
		_width,
		_height
	};
}

/**
 * It changes the position of the text.
 */
Vector2D Text::setPosition(const Vector2D &newPosition)
{
	return _position = newPosition;
}

/**
 * It changes the position of the text.
 */
Vector2D Text::setPosition(double x, double y)
{
	return _position = Vector2D(x, y);
}

/**
 * It changes the color of the text.
 */
SDL_Color Text::setColor(const SDL_Color &color)
{
	SDL_DestroyTexture(_textTexture);
	SDL_Surface *textSurface = TTF_RenderText_Solid(_font->getFont(), _text.c_str(), color);
	_textTexture = SDL_CreateTextureFromSurface(_font->getRenderer(), textSurface);
	SDL_FreeSurface(textSurface);
	return this->_color = color;
}

/**
 * It renders the text in the corrent position.
 */
void Text::render() const
{
	SDL_Rect rect{
		(int)_position.getX(),
		(int)_position.getY(),
		_width,
		_height
	};
	SDL_RenderCopy(_font->getRenderer(), _textTexture, nullptr, &rect);
}
