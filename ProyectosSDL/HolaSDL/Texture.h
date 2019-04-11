#pragma once

#include <string>
#include "SDL.h"

using namespace std;

class Texture {
 private:
  SDL_Texture *_texture = nullptr;
  SDL_Renderer *_renderer = nullptr;
  Uint32 _w = 0;
  Uint32 _h = 0;
  Uint32 _fw = 0;  // Frame width
  Uint32 _fh = 0;  // Frame height
  Uint32 _numCols = 1;
  Uint32 _numRows = 1;

 public:
  Texture(SDL_Renderer *r) : _renderer(r){};
  Texture(SDL_Renderer *r, string filename, Uint32 numRows = 1,
          Uint32 numCols = 1)
      : _renderer(r) {
    load(filename, numRows, numCols);
  };
  Texture(SDL_Texture *texture, SDL_Renderer *renderer, Uint32 w, Uint32 h,
          Uint32 fw, Uint32 fh, Uint32 numRows, Uint32 numCols);
  ~Texture() { liberate(); };
  void liberate();

  int getW() const { return _w; };
  int getH() const { return _h; };
  Uint32 getNumCols() const { return _numCols; };
  Uint32 getNumRows() const { return _numRows; };
  void setTexture(SDL_Texture *texture) {
    if (texture != _texture) {
      SDL_DestroyTexture(_texture);
      _texture = texture;
    }
  }
  SDL_Texture *getTexture() const { return _texture; };

  void load(string filename, Uint32 numRows = 1, Uint32 numCols = 1);
  void render(const SDL_Rect &rect,
              SDL_RendererFlip flip = SDL_FLIP_NONE) const;
  void renderFrame(const SDL_Rect &destRect, int row, int col, int angle = 0,
                   SDL_RendererFlip flip = SDL_FLIP_NONE) const;
};
