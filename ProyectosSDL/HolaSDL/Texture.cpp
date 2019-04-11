#include "Texture.h"
#include <iostream>
#include "SDLError.h"
#include "SDL_image.h"

using namespace std;

Texture::Texture(SDL_Renderer *r) : renderer_(r) {}  /// Public
Texture::Texture(SDL_Renderer *r, string filename, Uint32 numRows,
                 Uint32 numCols)
    : renderer_(r) {
  load(filename, numRows, numCols);
}  // Constructor
Texture::~Texture() { liberate(); }

int Texture::getW() const { return w_; }

int Texture::getH() const { return h_; }

Uint32 Texture::getNumCols() const { return numCols_; }

Uint32 Texture::getNumRows() const { return numRows_; }

void Texture::setTexture(SDL_Texture *texture) {
  if (texture != texture_) {
    SDL_DestroyTexture(texture_);
    texture_ = texture;
  }
}

SDL_Texture *Texture::getTexture() const { return texture_; }

Texture::Texture(SDL_Texture *texture, SDL_Renderer *renderer, Uint32 w,
                 Uint32 h, Uint32 fw, Uint32 fh, Uint32 numRows, Uint32 numCols)
    : renderer_(renderer),
      texture_(texture),
      w_(w),
      h_(h),
      fw_(fw),
      fh_(fh),
      numRows_(numRows),
      numCols_(numCols) {}

/// Public
// Loads a texture by its file name
void Texture::load(string filename, Uint32 nRows, Uint32 nCols) {
  SDL_Surface *tempSurface = IMG_Load(filename.c_str());
  if (tempSurface == nullptr)
    throw new (SDLError)("Error loading surface from " + filename);
  liberate();
  texture_ = SDL_CreateTextureFromSurface(renderer_, tempSurface);
  if (texture_ == nullptr)
    throw new (SDLError)("Error loading texture from " + filename);
  numRows_ = nRows;
  numCols_ = nCols;
  w_ = tempSurface->w;
  h_ = tempSurface->h;
  fw_ = w_ / numCols_;
  fh_ = h_ / numRows_;
  SDL_FreeSurface(tempSurface);
}

/// Public
// Frees memory
void Texture::liberate() {
  SDL_DestroyTexture(texture_);
  texture_ = nullptr;
  w_ = h_ = 0;
}

/// Public
// Defines the render behaviour
void Texture::render(const SDL_Rect &destRect, SDL_RendererFlip flip) const {
  SDL_Rect srcRect;
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = w_;
  srcRect.h = h_;
  SDL_RenderCopyEx(renderer_, texture_, &srcRect, &destRect, 0, 0, flip);
}

/// Public
// Renders the current frame
void Texture::renderFrame(const SDL_Rect &destRect, int row, int col, int angle,
                          SDL_RendererFlip flip) const {
  SDL_Rect srcRect;
  srcRect.x = fw_ * col;
  srcRect.y = fh_ * row;
  srcRect.w = fw_;
  srcRect.h = fh_;
  SDL_RenderCopyEx(renderer_, texture_, &srcRect, &destRect, angle, 0, flip);
}
