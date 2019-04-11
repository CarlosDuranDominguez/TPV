#pragma once
#include "ArkanoidError.h"

class SDLError final : public ArkanoidError {
 public:
  explicit SDLError(const string &m) : ArkanoidError("[SDL]: " + m) {}
};
