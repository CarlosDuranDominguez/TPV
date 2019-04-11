#pragma once
#include <functional>
#include "Text.h"

class Button : public Text {
  SDL_Color inColor_;
  SDL_Color outColor_;
  bool mouseIn_ = false;
  function<void()> callback_;

 public:
  Button(Font* font, float32 x, float32 y, float32 width, float32 height,
         SDL_Color inColor, SDL_Color outColor, string text,
         function<void()> callback);
  ~Button();
  virtual void handleEvents(SDL_Event event);
};
