#include "Font.h"
#include "FileNotFoundError.h"

/// Public
// Constructor
Font::Font(SDL_Renderer *renderer, string filename, int size)
    : _renderer(renderer), _size(size)
{
  load(filename);
}

/// Public
// Destructor
Font::~Font()
{
  liberate();
}

/// Public
// Gets the created font
TTF_Font *Font::getFont() const
{
  return _font;
}

/// Public
// Gets the renderer for this font
SDL_Renderer *Font::getRenderer() const
{
  return _renderer;
}

/// Public
// Closes the font from the TTF library and frees it
void Font::liberate()
{
  TTF_CloseFont(_font);
  _font = nullptr;
}

/// Public
// Load the font from a file path
void Font::load(string filename)
{
  _font = TTF_OpenFont(filename.c_str(), _size);
  if (_font == nullptr)
  {
    throw new FileNotFoundError(filename);
  }
}
