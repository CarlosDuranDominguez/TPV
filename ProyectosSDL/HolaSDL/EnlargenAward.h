#pragma once
#include "Award.h"

class EnlargenAward final : public Award {
 public:
  EnlargenAward();
  EnlargenAward(float32 x, float32 y, float32 width, float32 height,
                float32 speed, Uint32 frameRate, Texture* texture);
  void contact() override;
};
