#pragma once

#include "checkML.h"
#include "ArkanoidBody.h"

class Wall : public ArkanoidBody
{
private:
  void setBody(float32 x, float32 y, float32 width, float32 height, b2World &world);

public:
  Wall(){};
  Wall(float32 x, float32 y, float32 width, float32 height, Texture *texture);
  ~Wall(){};
  virtual void update();
  virtual void render() const;
  virtual std::istream &deserialize(std::istream &out);
  virtual std::ostream &serialize(std::ostream &is) const;
};
