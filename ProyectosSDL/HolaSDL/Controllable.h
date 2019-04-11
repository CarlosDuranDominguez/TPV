#pragma once
#include "SDL.h"

/*
 *Controllable interface
 */
class Controllable {
 public:
  Controllable(){};
  ~Controllable(){};
  virtual void handleEvents(SDL_Event event) = 0;
};
