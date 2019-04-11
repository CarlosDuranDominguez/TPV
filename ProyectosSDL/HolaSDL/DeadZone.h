#pragma once
#include "ArkanoidBody.h"

class DeadZone final : public ArkanoidBody {
  void setBody(float32 x, float32 y, float32 width, float32 height,
               b2World &world);

 public:
  DeadZone();
  DeadZone(float32 x, float32 y, float32 width, float32 height);
  ~DeadZone();
  void update() override;
  void render() const override;
  void onBeginContact(RigidBody *rigidBody) override;
  std::istream &deserialize(std::istream &out) override;
  std::ostream &serialize(std::ostream &is) const override;
};
