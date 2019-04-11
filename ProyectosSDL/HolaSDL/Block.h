#pragma once

#include "ArkanoidBody.h"

class Block : public ArkanoidBody {
 private:
  int _color;
  void setBody(float32 x, float32 y, float32 width, float32 height,
               b2World &world);

 public:
  Block(){};
  Block(float32 x, float32 y, float32 width, float32 height, int color,
        Texture *texture);
  ~Block(){};
  virtual void update();
  virtual void render() const;
  virtual void contact();
  virtual void destroy();
  virtual std::istream &deserialize(std::istream &out);
  virtual std::ostream &serialize(std::ostream &is) const;
  int getColor() const { return _color; };
};
