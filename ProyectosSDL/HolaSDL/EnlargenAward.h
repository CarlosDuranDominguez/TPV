#include "Award.h"

class EnlargenAward : public Award
{
public:
  EnlargenAward(){};
  EnlargenAward(float32 x, float32 y, float32 width, float32 height, float32 framerate, Texture *texture);
  virtual void contact();
};
