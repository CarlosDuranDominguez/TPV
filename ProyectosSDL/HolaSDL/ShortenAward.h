#include "Award.h"

class ShortenAward : public Award
{
public:
  ShortenAward(){};
  ShortenAward(float32 x, float32 y, float32 width, float32 height, float32 speed, float32 framerate, Texture *texture);
  virtual void contact();
};
