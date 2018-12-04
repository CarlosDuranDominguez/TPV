#include "Texture.h"
#include <iostream>

using namespace std;

void Texture::liberate()
{
	SDL_DestroyTexture(_texture);
	_texture = nullptr;
	_w = _h = 0;
}
Texture::Texture(SDL_Texture *texture, SDL_Renderer *renderer, uint w, uint h, uint fw, uint fh, uint numRows, uint numCols)
	:_renderer(renderer), _texture(texture), _w(w), _h(h), _fw(fw), _fh(fh), _numRows(numRows), _numCols(numCols){

}
void Texture::load(string filename, uint nRows, uint nCols)
{
	SDL_Surface *tempSurface = IMG_Load(filename.c_str());
	if (tempSurface == nullptr)
		throw "Error loading surface from " + filename;
	liberate();
	_texture = SDL_CreateTextureFromSurface(_renderer, tempSurface);
	if (_texture == nullptr)
		throw "Error loading texture from " + filename;
	_numRows = nRows;
	_numCols = nCols;
	_w = tempSurface->w;
	_h = tempSurface->h;
	_fw = _w / _numCols;
	_fh = _h / _numRows;
	SDL_FreeSurface(tempSurface);
}

void Texture::render(const SDL_Rect &destRect, SDL_RendererFlip flip) const
{
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = _w;
	srcRect.h = _h;
	SDL_RenderCopyEx(_renderer, _texture, &srcRect, &destRect, 0, 0, flip);
}

void Texture::renderFrame(const SDL_Rect &destRect, int row, int col, int angle, SDL_RendererFlip flip) const
{
	SDL_Rect srcRect;
	srcRect.x = _fw * col;
	srcRect.y = _fh * row;
	srcRect.w = _fw;
	srcRect.h = _fh;
	SDL_RenderCopyEx(_renderer, _texture, &srcRect, &destRect, angle, 0, flip);
}
