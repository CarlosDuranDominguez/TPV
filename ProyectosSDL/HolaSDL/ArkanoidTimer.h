#pragma once
#include <ctime>
#include "SDL.h"

class ArkanoidTimer {
  time_t *firstTime_;

 public:
  ArkanoidTimer();
  ~ArkanoidTimer();

  float getSeconds() const;
  void delay(Uint32 time) const;
  void reset() const;
};
