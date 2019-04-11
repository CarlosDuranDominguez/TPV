#pragma once
#include "SDL.h"

/*
 *Controllable interface
 */
class Controllable {
 public:
  Controllable();
  virtual ~Controllable();
  virtual void handleEvents(SDL_Event event) = 0;
};

inline Controllable::Controllable() {}

inline Controllable::~Controllable() {}
