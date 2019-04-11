#pragma once

#include "ArkanoidBody.h"

class DeadZone : public ArkanoidBody {
 private:
  void setBody(float32 x, float32 y, float32 width, float32 height,
               b2World &world);

 public:
  DeadZone(){};
  DeadZone(float32 x, float32 y, float32 width, float32 height);
  ~DeadZone(){};
  virtual void update(){};
  virtual void render() const {};
  virtual void onBeginContact(RigidBody *rigidBody);
  virtual std::istream &deserialize(std::istream &out);
  virtual std::ostream &serialize(std::ostream &is) const;
};
