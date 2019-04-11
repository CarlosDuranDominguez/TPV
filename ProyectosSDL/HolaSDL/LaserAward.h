#pragma once
#include "Award.h"

class LaserAward final : public Award {
 public:
  LaserAward();
  LaserAward(float32 x, float32 y, float32 width, float32 height, float32 speed,
             Uint32 frameRate, Texture *texture);
  void contact() override;
};
