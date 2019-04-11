#include "Font.h"
#include "FileNotFoundError.h"

Font::Font() {
} /// Public
// Constructor
Font::Font(SDL_Renderer *renderer, string filename, int size)
    : renderer_(renderer), size_(size) {
  load(filename);
}

/// Public
// Destructor
Font::~Font() { liberate(); }

/// Public
// Gets the created font
TTF_Font *Font::getFont() const { return font_; }

/// Public
// Gets the renderer for this font
SDL_Renderer *Font::getRenderer() const { return renderer_; }

/// Public
// Closes the font from the TTF library and frees it
void Font::liberate() {
  TTF_CloseFont(font_);
  font_ = nullptr;
}

/// Public
// Load the font from a file path
void Font::load(string filename) {
  font_ = TTF_OpenFont(filename.c_str(), size_);
  if (font_ == nullptr) {
    throw new FileNotFoundError(filename);
  }
}
