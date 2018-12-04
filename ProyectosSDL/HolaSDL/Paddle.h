#pragma once

#include "checkML.h"
#include "ArkanoidObject.h"
#include "RigidBody.h"
#include "Controllable.h"

class Game;

class Paddle : public ArkanoidObject, public RigidBody, public Controllable
{
private:
  bool _rightMovement, _leftMovement;
  float32 _speed;
  float32 _leftAnchor, _rightAnchor;
  void setBody(float32 x, float32 y, float32 width, float32 height, float32 anchorX, float32 limit, b2World &world);

public:
  Paddle();
  Paddle(float32 x, float32 y, float32 width, float32 height, float32 anchorX, float32 limit, float32 maxSpeed, Texture *texture);
  ~Paddle();
  virtual void update();
  virtual void afterUpdate();
  virtual void render() const;
  virtual void handleEvents(SDL_Event event);
  virtual void setWidth(float32 width);
  virtual void setPosition(b2Vec2 pos);
  virtual b2Vec2 getPosition() const { return RigidBody::getPosition(); };
  virtual void setPosition(float32 x, float32 y)
  {
    RigidBody::setPosition(b2Vec2{x, y});
    GameObject::setPosition(x, y);
  };
  virtual std::istream &deserialize(std::istream &out);
  virtual std::ostream &serialize(std::ostream &is) const;
};
