#pragma once

#include "ArkanoidError.h"

class SDLError : public ArkanoidError {
 public:
  SDLError(const string &m) : ArkanoidError("[SDL]: " + m) {}
};
