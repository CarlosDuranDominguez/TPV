#pragma once

#include "RigidBody.h"
#include "Game.h"

/// Public
// Destructor
RigidBody::~RigidBody()
{
  _body->DestroyFixture(_fixture);
  Game::getWorld()->DestroyBody(_body);
};

/// Public
// Constructor
RigidBody::RigidBody(b2BodyDef &body, b2Shape &shape, b2FixtureDef &fixtureDef, b2World &world)
{
  // Set the fixture definition
  setUp(shape, fixtureDef);
}

/// Public
// Sets the linear velocity for this rigid body
void RigidBody::setVelocity(b2Vec2 &velocity)
{
  _body->SetLinearVelocity(velocity);
}

/// Public
// Sets the position for this rigid body, keeping the angle
void RigidBody::setPosition(b2Vec2 &position)
{
  _body->SetTransform(position, _body->GetAngle());
}

/// Public
// Sets the angle for this rigid body
void RigidBody::setAngle(float32 angle)
{
  _body->SetTransform(_body->GetPosition(), angle);
}

/// Public
// Sets the position and angle for this rigid body
void RigidBody::setTransform(b2Vec2 &position, float32 angle)
{
  _body->SetTransform(position, angle);
}

/// Public
// Applies a force to this rigid body
void RigidBody::applyForce(b2Vec2 &force, b2Vec2 &point)
{
  _body->ApplyForce(force, point, true);
}

/// Public
// Applies a force to the body's center
void RigidBody::applyForceToCenter(b2Vec2 &force)
{
  _body->ApplyForceToCenter(force, true);
}

/// Public
// Applies a linear impulse to this rigid body
void RigidBody::ApplyLinearImpulse(b2Vec2 &impulse, b2Vec2 &point)
{
  _body->ApplyLinearImpulse(impulse, point, true);
}

/// Public
// Applies a linear impuse to this rigid body's center
void RigidBody::ApplyLinearImpulseToCenter(b2Vec2 &impulse)
{
  _body->ApplyLinearImpulseToCenter(impulse, true);
}

/// Protected
// Sets up the shape by creating a fixture from the shape
void RigidBody::setUp(b2Shape &shape, b2FixtureDef &fixture)
{

  // Join the fixture to the shape
  fixture.shape = &shape;
  // Create the fixture
  _fixture = _body->CreateFixture(&fixture);
}
