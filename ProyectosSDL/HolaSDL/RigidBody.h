#pragma once
#include <Box2D/Box2D.h>

class RigidBody
{
protected:
  b2Body *_body;
  b2Fixture *_fixture;
  void setUp(b2Shape &shape, b2FixtureDef &fixture);

public:
  RigidBody(){};
  RigidBody(b2BodyDef &body, b2Shape &shape, b2FixtureDef &fixtureDef, b2World &world);
  ~RigidBody();
  b2Body *getBody() { return _body; };
  void setVelocity(b2Vec2 &velocity);
  void setPosition(b2Vec2 &position);
  void setAngle(float32 angle);
  void setTransform(b2Vec2 &position, float32 angle);
  virtual void onBeginContact(RigidBody *body){};
  virtual void onEndContact(RigidBody *body){};
  virtual b2Vec2 getPosition() const { return _body->GetPosition(); }
  b2Vec2 getVelocity() const { return _body->GetLinearVelocity(); }
  float32 getAngle() const { return _body->GetAngle(); }

  void applyForce(b2Vec2 &force, b2Vec2 &point);
  void applyForceToCenter(b2Vec2 &force);
  void ApplyLinearImpulse(b2Vec2 &impulse, b2Vec2 &point);
  void ApplyLinearImpulseToCenter(b2Vec2 &impulse);
};
