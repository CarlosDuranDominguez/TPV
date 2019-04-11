#include "Text.h"

// Constructor
Text::Text(Font *font, const float32 x, const float32 y, const float32 width,
           const float32 height, const SDL_Color &color, const string &text)
    : GameObject(x, y, width, height),
      font_(font),
      text_(text),
      color_(color),
      width_(int(width)),
      height_(int(height)) {
  TTF_SizeText(font_->getFont(), text.c_str(), &width_, &height_);
  const auto textSurface =
      TTF_RenderText_Solid(font->getFont(), text.c_str(), color);
  const auto textTexture =
      SDL_CreateTextureFromSurface(font->getRenderer(), textSurface);
  texture_ = new Texture(textTexture, font->getRenderer(), width_, height_,
                         width_, height_, 1, 1);
  SDL_FreeSurface(textSurface);
}
// Destructor
Text::~Text() { delete texture_; }

// Sets the text for this instance
void Text::setText(const string &newText) {
  text_ = newText;
  TTF_SizeText(font_->getFont(), newText.c_str(), &width_, &height_);
  const auto textSurface =
      TTF_RenderText_Solid(font_->getFont(), newText.c_str(), color_);
  texture_->setTexture(
      SDL_CreateTextureFromSurface(font_->getRenderer(), textSurface));
  SDL_FreeSurface(textSurface);
}

// Gets the text box
SDL_Rect Text::getRect() const {
  return {int(position_.x), int(position_.y), width_, height_};
}

// Set the text color
SDL_Color Text::setColor(const SDL_Color &color) {
  const auto textSurface =
      TTF_RenderText_Solid(font_->getFont(), text_.c_str(), color);
  texture_->setTexture(
      SDL_CreateTextureFromSurface(font_->getRenderer(), textSurface));
  SDL_FreeSurface(textSurface);
  return this->color_ = color;
}

// Defines the render behaviour
void Text::render() const {
  SDL_Rect rect{int(position_.x), int(position_.y), width_, height_};
  SDL_RenderCopy(font_->getRenderer(), texture_->getTexture(), nullptr, &rect);
}

// Defines the deserialize method behaviour to patch the instance when loading a
// file save
std::istream &Text::deserialize(std::istream &out) { return out; }

// Defines the serialize method behaviour to save the data into a file save
std::ostream &Text::serialize(std::ostream &is) const { return is; }
