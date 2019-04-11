#include "Texture.h"
#include "SDLError.h"
#include "SDL_image.h"

using namespace std;

Texture::Texture(SDL_Renderer *r) : renderer_(r) {}
Texture::Texture(SDL_Renderer *r, const string &filename, const Uint32 numRows,
                 const Uint32 numCols)
    : renderer_(r) {
  load(filename, numRows, numCols);
}

Texture::Texture(SDL_Texture *texture, SDL_Renderer *renderer, const Uint32 w,
                 const Uint32 h, const Uint32 fw, const Uint32 fh,
                 const Uint32 numRows, const Uint32 numCols)
    : texture_(texture),
      renderer_(renderer),
      w_(w),
      h_(h),
      fw_(fw),
      fh_(fh),
      numCols_(numCols),
      numRows_(numRows) {}

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

// Loads a texture by its file name
void Texture::load(const string &filename, const Uint32 nRows,
                   const Uint32 nCols) {
  const auto tempSurface = IMG_Load(filename.c_str());
  if (tempSurface == nullptr)
    throw SDLError("Error loading surface from " + filename);
  liberate();
  texture_ = SDL_CreateTextureFromSurface(renderer_, tempSurface);
  if (texture_ == nullptr)
    throw SDLError("Error loading texture from " + filename);
  numRows_ = nRows;
  numCols_ = nCols;
  w_ = tempSurface->w;
  h_ = tempSurface->h;
  fw_ = w_ / numCols_;
  fh_ = h_ / numRows_;
  SDL_FreeSurface(tempSurface);
}

// Frees memory
void Texture::liberate() {
  SDL_DestroyTexture(texture_);
  texture_ = nullptr;
  w_ = h_ = 0;
}

// Defines the render behaviour
void Texture::render(const SDL_Rect &rect, const SDL_RendererFlip flip) const {
  SDL_Rect srcRect;
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = w_;
  srcRect.h = h_;
  SDL_RenderCopyEx(renderer_, texture_, &srcRect, &rect, 0, nullptr, flip);
}

// Renders the current frame
void Texture::renderFrame(const SDL_Rect &destRect, const int row,
                          const int col, const int angle,
                          const SDL_RendererFlip flip) const {
  SDL_Rect srcRect{int(fw_ * col), int(fh_ * row), int(fw_), int(fh_)};
  SDL_RenderCopyEx(renderer_, texture_, &srcRect, &destRect, angle, nullptr,
                   flip);
}
