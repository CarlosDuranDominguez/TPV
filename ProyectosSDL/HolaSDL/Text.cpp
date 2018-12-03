#include "Text.h"

/**
 * Constructors.
 */
Text::Text(Font *font, float x, float y, int width, int height, const SDL_Color &color, const string &text)
	: _font(font), GameObject(x,y,width,height), _color(color), _text(text)
{
	
	TTF_SizeText(_font->getFont(), text.c_str(), &width, &height);
	SDL_Surface *textSurface = TTF_RenderText_Solid(font->getFont(), text.c_str(), color);
	SDL_Texture* _textTexture = SDL_CreateTextureFromSurface(font->getRenderer(), textSurface);
	_texture = new Texture(_textTexture, font->getRenderer(), width, height, width, height,1,1);
	SDL_FreeSurface(textSurface);
}

/**
 * Destructor.
 */
Text::~Text()
{
	delete _texture;
}

/**
 * It changes the text by newText.
 */
void Text::setText(const string newText)
{
	_text = newText;
	int width = _texture->getW(), height = _texture->getH();
	TTF_SizeText(_font->getFont(), newText.c_str(), &width, &height);
	SDL_Surface *textSurface = TTF_RenderText_Solid(_font->getFont(), newText.c_str(), _color);
	_texture->setTexture(SDL_CreateTextureFromSurface(_font->getRenderer(), textSurface));
	SDL_FreeSurface(textSurface);
}

/**
 * It gets the rect of the text.
 */
SDL_Rect Text::getRect() const
{
	return {
		(int)_position.x,
		(int)_position.y,
		_texture->getW(),
		_texture->getH() };
}

/**
 * It changes the color of the text.
 */
SDL_Color Text::setColor(const SDL_Color &color)
{
	SDL_Surface *textSurface = TTF_RenderText_Solid(_font->getFont(), _text.c_str(), color);
	_texture->setTexture(SDL_CreateTextureFromSurface(_font->getRenderer(), textSurface));
	SDL_FreeSurface(textSurface);
	return this->_color = color;
}

/**
 * It renders the text in the corrent position.
 */
void Text::render() const
{
	SDL_Rect rect {
		(int)_position.x,
		(int)_position.y,
		_texture->getW(),
		_texture->getH()};
	SDL_RenderCopy(_font->getRenderer(), _texture->getTexture(), nullptr, &rect);
}

std::istream& Text::deserialize(std::istream& out) {
	return out;
}

std::ostream& Text::serialize(std::ostream& is) const {
	return is;
}