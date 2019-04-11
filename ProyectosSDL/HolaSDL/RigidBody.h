#pragma once
#include <Box2D/Box2D.h>

class RigidBody {
 protected:
  b2Body *body_;
  b2Fixture *fixture_;
  void setUp(b2Shape &shape, b2FixtureDef &fixture);

 public:
  RigidBody();
  RigidBody(b2BodyDef &body, b2Shape &shape, b2FixtureDef &fixtureDef,
            b2World &world);
  virtual ~RigidBody();
  b2Body *getBody() const;
  void setVelocity(b2Vec2 &velocity) const;
  void setPosition(b2Vec2 &position) const;
  void setAngle(float32 angle) const;
  void setTransform(b2Vec2 &position, float32 angle) const;
  virtual void onBeginContact(RigidBody *body);
  virtual void onEndContact(RigidBody *body);
  virtual b2Vec2 getPosition() const;
  b2Vec2 getVelocity() const;
  float32 getAngle() const;

  void applyForce(b2Vec2 &force, b2Vec2 &point) const;
  void applyForceToCenter(b2Vec2 &force) const;
  void applyLinearImpulse(b2Vec2 &impulse, b2Vec2 &point) const;
  void applyLinearImpulseToCenter(b2Vec2 &impulse) const;
};
