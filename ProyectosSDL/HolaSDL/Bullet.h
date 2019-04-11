#pragma once
#include "Ball.h"

class Bullet final : public Ball {
  void setBody(float32 x, float32 y, float32 radius, b2World &world) override;

 public:
  Bullet();
  Bullet(float32 x, float32 y, float32 radius, float32 speed, Texture *texture);
  ~Bullet();
  void onBeginContact(RigidBody *rigidBody) override;
  std::istream &deserialize(std::istream &out) override;
  std::ostream &serialize(std::ostream &is) const override;
};
