#pragma once

#include "checkML.h"
#include "ArkanoidBody.h"
#include "Controllable.h"
#include "Ball.h"

class Game;

class Paddle : public ArkanoidBody, public Controllable
{
private:
  bool _rightMovement, _leftMovement;
  float32 _speed;
  float32 _leftAnchor, _rightAnchor;
  b2Joint* _ballJointA, *_ballJointB;
  Ball* _ball;
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
  void jointTo(Ball* ball);
  void splitFromBall();
  virtual std::istream &deserialize(std::istream &out);
  virtual std::ostream &serialize(std::ostream &is) const;
};
