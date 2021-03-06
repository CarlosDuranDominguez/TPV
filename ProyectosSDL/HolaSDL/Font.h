#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Texture.h"

class Font {
  TTF_Font *font_ = nullptr;
  SDL_Renderer *renderer_;
  Uint32 size_ = 8;

 public:
  Font();
  Font(SDL_Renderer *renderer, const string& filename, int size);
  ~Font();
  TTF_Font *getFont() const;
  SDL_Renderer *getRenderer() const;
  void liberate();
  void load(const string& filename);
};
