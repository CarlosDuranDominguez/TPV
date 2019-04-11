#include "Text.h"

/// Public
// Constructor
Text::Text(Font *font, float32 x, float32 y, float32 width, float32 height,
           const SDL_Color &color, const string &text)
    : font_(font), GameObject(x, y, width, height), color_(color), text_(text) {
  TTF_SizeText(font_->getFont(), text.c_str(), &width_, &height_);
  SDL_Surface *textSurface =
      TTF_RenderText_Solid(font->getFont(), text.c_str(), color);
  SDL_Texture *_textTexture =
      SDL_CreateTextureFromSurface(font->getRenderer(), textSurface);
  texture_ = new Texture(_textTexture, font->getRenderer(), width_, height_,
                         width_, height_, 1, 1);
  SDL_FreeSurface(textSurface);
}
/// Public
// Destructor
Text::~Text() { delete texture_; }

/// Public
// Sets the text for this instance
void Text::setText(const string newText) {
  text_ = newText;
  TTF_SizeText(font_->getFont(), newText.c_str(), &width_, &height_);
  SDL_Surface *textSurface =
      TTF_RenderText_Solid(font_->getFont(), newText.c_str(), color_);
  texture_->setTexture(
      SDL_CreateTextureFromSurface(font_->getRenderer(), textSurface));
  SDL_FreeSurface(textSurface);
}

/// Public
// Gets the text box
SDL_Rect Text::getRect() const {
  return {(int)position_.x, (int)position_.y, width_, height_};
}

/// Public
// Set the text color
SDL_Color Text::setColor(const SDL_Color &color) {
  SDL_Surface *textSurface =
      TTF_RenderText_Solid(font_->getFont(), text_.c_str(), color);
  texture_->setTexture(
      SDL_CreateTextureFromSurface(font_->getRenderer(), textSurface));
  SDL_FreeSurface(textSurface);
  return this->color_ = color;
}

/// Public Virtual
// Defines the render behaviour
void Text::render() const {
  SDL_Rect rect{(int)position_.x, (int)position_.y, width_, height_};
  SDL_RenderCopy(font_->getRenderer(), texture_->getTexture(), nullptr, &rect);
}

/// Public Virtual
// Defines the deserialize method behaviour to patch the instance when loading a
// file save
std::istream &Text::deserialize(std::istream &out) { return out; }

/// Public Virtual
// Defines the serialize method behaviour to save the data into a file save
std::ostream &Text::serialize(std::ostream &is) const { return is; }
