#include "RigidBody.h"
#include <iostream>
#include "Game.h"

RigidBody::RigidBody() : body_(nullptr), fixture_(nullptr) {}

// Constructor
RigidBody::RigidBody(b2BodyDef &, b2Shape &shape, b2FixtureDef &fixtureDef,
                     b2World &)
    : body_(nullptr), fixture_(nullptr) {
  // Set the fixture definition
  setUp(shape, fixtureDef);
}

// Destructor
RigidBody::~RigidBody() {
  if (body_) {
    body_->DestroyFixture(fixture_);
    Game::getWorld()->DestroyBody(body_);
    body_ = nullptr;
  } else {
    cerr << "Attempted to destroy a null body.";
  }
}

// Sets the linear velocity for this rigid body
void RigidBody::setVelocity(b2Vec2 &velocity) const {
  body_->SetLinearVelocity(velocity);
}

// Sets the position for this rigid body, keeping the angle
void RigidBody::setPosition(b2Vec2 &position) const {
  body_->SetTransform(position, body_->GetAngle());
}

// Sets the angle for this rigid body
void RigidBody::setAngle(const float32 angle) const {
  body_->SetTransform(body_->GetPosition(), angle);
}

// Sets the position and angle for this rigid body
void RigidBody::setTransform(b2Vec2 &position, const float32 angle) const {
  body_->SetTransform(position, angle);
}

// Applies a force to this rigid body
void RigidBody::applyForce(b2Vec2 &force, b2Vec2 &point) const {
  body_->ApplyForce(force, point, true);
}

// Applies a force to the body's center
void RigidBody::applyForceToCenter(b2Vec2 &force) const {
  body_->ApplyForceToCenter(force, true);
}

// Applies a linear impulse to this rigid body
void RigidBody::applyLinearImpulse(b2Vec2 &impulse, b2Vec2 &point) const {
  body_->ApplyLinearImpulse(impulse, point, true);
}

// Applies a linear impulse to this rigid body's center
void RigidBody::applyLinearImpulseToCenter(b2Vec2 &impulse) const {
  body_->ApplyLinearImpulseToCenter(impulse, true);
}

// Sets up the shape by creating a fixture from the shape
void RigidBody::setUp(b2Shape &shape, b2FixtureDef &fixture) {
  // Join the fixture to the shape
  fixture.shape = &shape;
  // Create the fixture
  fixture_ = body_->CreateFixture(&fixture);
}

b2Body *RigidBody::getBody() const { return body_; }

void RigidBody::onBeginContact(RigidBody *) {}

void RigidBody::onEndContact(RigidBody *) {}

b2Vec2 RigidBody::getPosition() const { return body_->GetPosition(); }

b2Vec2 RigidBody::getVelocity() const { return body_->GetLinearVelocity(); }

float32 RigidBody::getAngle() const { return body_->GetAngle(); }
