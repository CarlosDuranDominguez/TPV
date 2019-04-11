#include "Award.h"

class LaserAward : public Award {
 public:
  LaserAward(){};
  LaserAward(float32 x, float32 y, float32 width, float32 height, float32 speed,
             uint framerate, Texture *texture);
  virtual void contact();
};
