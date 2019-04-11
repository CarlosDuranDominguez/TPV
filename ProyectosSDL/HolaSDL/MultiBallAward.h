#include "Award.h"

class MultiBallAward : public Award {
 public:
  MultiBallAward(){};
  MultiBallAward(float32 x, float32 y, float32 width, float32 height,
                 float32 speed, uint framerate, Texture *texture);
  virtual void contact();
};
