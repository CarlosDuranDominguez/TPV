#include "Font.h"

Font::Font(SDL_Renderer *renderer, string filename, int size)
	: _renderer(renderer), _size(size)
{
	load(filename);
}

Font::~Font()
{
	liberate();
}

TTF_Font *Font::getFont() const
{
	return _font;
}

SDL_Renderer *Font::getRenderer() const
{
	return _renderer;
}

void Font::liberate()
{
	TTF_CloseFont(_font);
	_font = nullptr;
}

void Font::load(string filename)
{
	_font = TTF_OpenFont(filename.c_str(), _size);
	if (_font == nullptr)
	{
		throw "Error loading font";
	}
}
