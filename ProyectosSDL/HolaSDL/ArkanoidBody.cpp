#include "ArkanoidBody.h"

ArkanoidBody::ArkanoidBody() = default;

// Constructor
ArkanoidBody::ArkanoidBody(const float32 x, const float32 y,
                           const float32 width, const float32 height,
                           Texture *texture)
    : ArkanoidObject(x, y, width, height, texture) {}
ArkanoidBody::~ArkanoidBody() = default;

// Get the position for this rigid body
b2Vec2 ArkanoidBody::getPosition() const { return RigidBody::getPosition(); }

// Set the position for this rigid body
void ArkanoidBody::setPosition(const float32 x, const float32 y) {
  RigidBody::setPosition(b2Vec2{x, y});
  GameObject::setPosition(x, y);
}
