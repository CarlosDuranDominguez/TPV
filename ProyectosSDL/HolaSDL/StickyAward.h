#include "Award.h"

class StickyAward : public Award
{
public:
  StickyAward(){};
  StickyAward(float32 x, float32 y, float32 width, float32 height, float32 speed, uint framerate, Texture *texture)
      : Award(x, y, width, height, speed, framerate, texture){};
  virtual void contact();
};
