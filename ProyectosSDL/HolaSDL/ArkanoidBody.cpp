#include "ArkanoidBody.h"

/// Public
/// Constructor
ArkanoidBody::ArkanoidBody(float32 x, float32 y, float32 width, float32 height, Texture *texture)
    : ArkanoidObject(x, y, width, height, texture) {}

/// Public Virtual
/// Get the position for this rigid body
b2Vec2 ArkanoidBody::getPosition() const
{
  return RigidBody::getPosition();
}

/// Public Virtual
/// Set the position for this rigid body
void ArkanoidBody::setPosition(float32 x, float32 y)
{
  RigidBody::setPosition(b2Vec2{x, y});
  GameObject::setPosition(x, y);
}
