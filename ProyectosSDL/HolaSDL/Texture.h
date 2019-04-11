#pragma once
#include <string>
#include "SDL.h"

using namespace std;

class Texture {
  SDL_Texture *texture_ = nullptr;
  SDL_Renderer *renderer_ = nullptr;
  Uint32 w_ = 0;
  Uint32 h_ = 0;
  Uint32 fw_ = 0;  // Frame width
  Uint32 fh_ = 0;  // Frame height
  Uint32 numCols_ = 1;
  Uint32 numRows_ = 1;

 public:
  explicit Texture(SDL_Renderer *r);
  Texture(SDL_Renderer *r, const string& filename, Uint32 numRows = 1,
          Uint32 numCols = 1);
  Texture(SDL_Texture *texture, SDL_Renderer *renderer, Uint32 w, Uint32 h,
          Uint32 fw, Uint32 fh, Uint32 numRows, Uint32 numCols);
  ~Texture();
  void liberate();

  int getW() const;
  int getH() const;
  Uint32 getNumCols() const;
  Uint32 getNumRows() const;
  void setTexture(SDL_Texture *texture);
  SDL_Texture *getTexture() const;

  void load(const string& filename, Uint32 numRows = 1, Uint32 numCols = 1);
  void render(const SDL_Rect &rect,
              SDL_RendererFlip flip = SDL_FLIP_NONE) const;
  void renderFrame(const SDL_Rect &destRect, int row, int col, int angle = 0,
                   SDL_RendererFlip flip = SDL_FLIP_NONE) const;
};
