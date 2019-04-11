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
  b2Body *getBody();
  void setVelocity(b2Vec2 &velocity);
  void setPosition(b2Vec2 &position);
  void setAngle(float32 angle);
  void setTransform(b2Vec2 &position, float32 angle);
  virtual void onBeginContact(RigidBody *body);
  virtual void onEndContact(RigidBody *body);
  virtual b2Vec2 getPosition() const;
  b2Vec2 getVelocity() const;
  float32 getAngle() const;

  void applyForce(b2Vec2 &force, b2Vec2 &point);
  void applyForceToCenter(b2Vec2 &force);
  void applyLinearImpulse(b2Vec2 &impulse, b2Vec2 &point);
  void applyLinearImpulseToCenter(b2Vec2 &impulse);
};
