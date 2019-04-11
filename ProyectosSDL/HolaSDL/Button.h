#pragma once

#include <functional>
#include "Text.h"
#include "checkML.h"

class Button : public Text {
 private:
  SDL_Color _inColor;
  SDL_Color _outColor;
  bool _mouseIn = false;
  function<void()> _callback;

 public:
  Button(Font *font, float32 x, float32 y, float32 width, float32 height,
         SDL_Color inColor, SDL_Color outColor, string text,
         function<void()> callback)
      : Text(font, x, y, width, height, outColor, text),
        _inColor(inColor),
        _outColor(outColor),
        _callback(callback){};
  ~Button(){};
  virtual void handleEvents(SDL_Event event);
};
