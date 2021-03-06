#pragma once
#include "ArkanoidBody.h"

class Ball : public ArkanoidBody {
  virtual void setBody(float32 x, float32 y, float32 radius, b2World &world);
  float32 speed_;

 public:
  Ball();
  Ball(float32 x, float32 y, float32 radius, float32 speed, Texture *texture);
  ~Ball();
  float32 getSpeed() const;
  void setSpeed(float32 speed);
  virtual void destroy();
  virtual void update();
  virtual void render() const;
  virtual void afterUpdate();
  virtual void onEndContact(RigidBody *rigidBody);
  virtual std::istream &deserialize(std::istream &out);
  virtual std::ostream &serialize(std::ostream &is) const;
};
