#pragma once
#include "Award.h"

class MultiBallAward final : public Award {
 public:
  MultiBallAward();
  MultiBallAward(float32 x, float32 y, float32 width, float32 height,
                 float32 speed, Uint32 frameRate, Texture *texture);
  void contact() override;
};
