#pragma once
#include "Award.h"

class NextLevelAward final : public Award {
 public:
  NextLevelAward();
  NextLevelAward(float32 x, float32 y, float32 width, float32 height,
                 float32 speed, Uint32 frameRate, Texture *texture);
  void contact() override;
};
