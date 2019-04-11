#pragma once

#include "ArkanoidObject.h"
#include "RigidBody.h"

class ArkanoidBody : public ArkanoidObject, public RigidBody {
 public:
  ArkanoidBody();
  ArkanoidBody(float32 x, float32 y, float32 width, float32 height,
               Texture* texture);
  ~ArkanoidBody();
  virtual b2Vec2 getPosition() const;
  virtual void setPosition(float32 x, float32 y);
};
