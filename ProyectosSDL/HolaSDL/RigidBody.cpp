#pragma once

#include "RigidBody.h"
#include "Game.h"

/// Public
/// Destructor
RigidBody::~RigidBody()
{
  _body->DestroyFixture(_fixture);
  Game::getWorld()->DestroyBody(_body);
};

/// Public
/// Constructor
RigidBody::RigidBody(b2BodyDef &body, b2Shape &shape, b2FixtureDef &fixtureDef, b2World &world)
{
  // Set the fixture definition
  setUp(shape, fixtureDef);
}

void RigidBody::setUp(b2Shape &shape, b2FixtureDef &fixture)
{

  // Join the fixture to the shape
  fixture.shape = &shape;
  // Create the fixture
  _fixture = _body->CreateFixture(&fixture);
}

void RigidBody::setVelocity(b2Vec2 &velocity)
{
  _body->SetLinearVelocity(velocity);
}

void RigidBody::setPosition(b2Vec2 &position)
{
  _body->SetTransform(position, _body->GetAngle());
}

void RigidBody::setAngle(float32 angle)
{
  _body->SetTransform(_body->GetPosition(), angle);
}

void RigidBody::setTransform(b2Vec2 &position, float32 angle)
{
  _body->SetTransform(position, angle);
}

void RigidBody::applyForce(b2Vec2 &force, b2Vec2 &point)
{
  _body->ApplyForce(force, point, true);
}

void RigidBody::applyForceToCenter(b2Vec2 &force)
{
  _body->ApplyForceToCenter(force, true);
}

void RigidBody::ApplyLinearImpulse(b2Vec2 &impulse, b2Vec2 &point)
{
  _body->ApplyLinearImpulse(impulse, point, true);
}

void RigidBody::ApplyLinearImpulseToCenter(b2Vec2 &impulse)
{
  _body->ApplyLinearImpulseToCenter(impulse, true);
}
