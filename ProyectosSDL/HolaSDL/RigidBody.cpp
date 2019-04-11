#pragma once

#include "RigidBody.h"
#include "Game.h"

/// Public
// Destructor
RigidBody::~RigidBody() {
  body_->DestroyFixture(fixture_);
  Game::getWorld()->DestroyBody(body_);
};

/// Public
// Constructor
RigidBody::RigidBody(b2BodyDef &body, b2Shape &shape, b2FixtureDef &fixtureDef,
                     b2World &world) {
  // Set the fixture definition
  setUp(shape, fixtureDef);
}

/// Public
// Sets the linear velocity for this rigid body
void RigidBody::setVelocity(b2Vec2 &velocity) {
  body_->SetLinearVelocity(velocity);
}

/// Public
// Sets the position for this rigid body, keeping the angle
void RigidBody::setPosition(b2Vec2 &position) {
  body_->SetTransform(position, body_->GetAngle());
}

/// Public
// Sets the angle for this rigid body
void RigidBody::setAngle(float32 angle) {
  body_->SetTransform(body_->GetPosition(), angle);
}

/// Public
// Sets the position and angle for this rigid body
void RigidBody::setTransform(b2Vec2 &position, float32 angle) {
  body_->SetTransform(position, angle);
}

/// Public
// Applies a force to this rigid body
void RigidBody::applyForce(b2Vec2 &force, b2Vec2 &point) {
  body_->ApplyForce(force, point, true);
}

/// Public
// Applies a force to the body's center
void RigidBody::applyForceToCenter(b2Vec2 &force) {
  body_->ApplyForceToCenter(force, true);
}

/// Public
// Applies a linear impulse to this rigid body
void RigidBody::applyLinearImpulse(b2Vec2 &impulse, b2Vec2 &point) {
  body_->ApplyLinearImpulse(impulse, point, true);
}

/// Public
// Applies a linear impuse to this rigid body's center
void RigidBody::applyLinearImpulseToCenter(b2Vec2 &impulse) {
  body_->ApplyLinearImpulseToCenter(impulse, true);
}

/// Protected
// Sets up the shape by creating a fixture from the shape
void RigidBody::setUp(b2Shape &shape, b2FixtureDef &fixture) {
  // Join the fixture to the shape
  fixture.shape = &shape;
  // Create the fixture
  fixture_ = body_->CreateFixture(&fixture);
}

RigidBody::RigidBody() {
}

b2Body* RigidBody::getBody() { return body_; }

void RigidBody::onBeginContact(RigidBody* body) {
}

void RigidBody::onEndContact(RigidBody* body) {
}

b2Vec2 RigidBody::getPosition() const { return body_->GetPosition(); }

b2Vec2 RigidBody::getVelocity() const { return body_->GetLinearVelocity(); }

float32 RigidBody::getAngle() const { return body_->GetAngle(); }
