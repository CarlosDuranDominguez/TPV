#include "Font.h"
#include "FileNotFoundError.h"

Font::Font() : renderer_(nullptr) {}

// Constructor
Font::Font(SDL_Renderer *renderer, const string& filename, const int size)
    : renderer_(renderer), size_(size) {
  load(filename);
}

// Destructor
Font::~Font() { liberate(); }

// Gets the created font
TTF_Font *Font::getFont() const { return font_; }

// Gets the renderer for this font
SDL_Renderer *Font::getRenderer() const { return renderer_; }

// Closes the font from the TTF library and frees it
void Font::liberate() {
  TTF_CloseFont(font_);
  font_ = nullptr;
}

// Load the font from a file path
void Font::load(const string &filename) {
  font_ = TTF_OpenFont(filename.c_str(), size_);
  if (font_ == nullptr) {
    throw FileNotFoundError(filename);
  }
}
