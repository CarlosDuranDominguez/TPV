#include "ArkanoidBody.h"

ArkanoidBody::ArkanoidBody(float32 x, float32 y, float32 width, float32 height, Texture *texture)
    : ArkanoidObject(x, y, width, height, texture)
{
}

ArkanoidBody::~ArkanoidBody()
{
}

b2Vec2 ArkanoidBody::getPosition() const
{
  return RigidBody::getPosition();
}

void ArkanoidBody::setPosition(float32 x, float32 y)
{
  RigidBody::setPosition(b2Vec2{x, y});
  GameObject::setPosition(x, y);
}
