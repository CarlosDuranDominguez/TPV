#include "Font.h"
#include "FileNotFoundError.h"

/// Public
/// Constructor
Font::Font(SDL_Renderer *renderer, string filename, int size)
    : _renderer(renderer), _size(size)
{
  load(filename);
}

/// Public
/// Destructor
Font::~Font()
{
  liberate();
}

/**
 * It gets the created font.
 */
TTF_Font *Font::getFont() const
{
  return _font;
}

/**
 * It gets the renderer of the font.
 */
SDL_Renderer *Font::getRenderer() const
{
  return _renderer;
}

/**
 * It frees memory of the font.
 */
void Font::liberate()
{
  TTF_CloseFont(_font);
  _font = nullptr;
}

/**
 * It loads the font from the filename.
 */
void Font::load(string filename)
{
  _font = TTF_OpenFont(filename.c_str(), _size);
  if (_font == nullptr)
  {
    throw new FileNotFoundError(filename);
  }
}
