#pragma once
#include "Award.h"

class StickyAward final : public Award {
 public:
  StickyAward();
  StickyAward(float32 x, float32 y, float32 width, float32 height,
              float32 speed, Uint32 framerate, Texture* texture);
  void contact() override;
};
