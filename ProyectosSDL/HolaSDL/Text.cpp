#include "Text.h"

/// Public
/// Constructor
Text::Text(Font *font, float32 x, float32 y, float32 width, float32 height, const SDL_Color &color, const string &text)
    : _font(font), GameObject(x, y, width, height), _color(color), _text(text)
{

  TTF_SizeText(_font->getFont(), text.c_str(), &_width, &_height);
  SDL_Surface *textSurface = TTF_RenderText_Solid(font->getFont(), text.c_str(), color);
  SDL_Texture *_textTexture = SDL_CreateTextureFromSurface(font->getRenderer(), textSurface);
  _texture = new Texture(_textTexture, font->getRenderer(), _width, _height, _width, _height, 1, 1);
  SDL_FreeSurface(textSurface);
}
/// Public
/// Destructor
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
  TTF_SizeText(_font->getFont(), newText.c_str(), &_width, &_height);
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
      _width,
      _height};
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

/// Public Virtual
/// Defines the render behaviour
void Text::render() const
{
  SDL_Rect rect{
      (int)_position.x,
      (int)_position.y,
      _width,
      _height};
  SDL_RenderCopy(_font->getRenderer(), _texture->getTexture(), nullptr, &rect);
}

/// Public Virtual
/// Defines the deserialize method behaviour to patch the instance when loading a file save
std::istream &Text::deserialize(std::istream &out)
{
  return out;
}

/// Public Virtual
/// Defines the serialize method behaviour to save the data into a file save
std::ostream &Text::serialize(std::ostream &is) const
{
  return is;
}
