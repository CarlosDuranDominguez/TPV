#pragma once

#include <list>
#include "ArkanoidBody.h"
#include "Ball.h"
#include "Controllable.h"
#include "functional"

class Game;
enum ACTIONS { NONE, BEGIN, STICKY, LASER };
class Paddle : public ArkanoidBody, public Controllable {
  class ArkanoidJoint {
   public:
    ArkanoidJoint(Ball *ball, b2Vec2 &distance);
    ~ArkanoidJoint();
    b2Vec2 _distance;
    Ball *_ball;
  };

 private:
  bool _rightMovement, _leftMovement;
  float32 _speed;
  float32 _leftAnchor, _rightAnchor;
  std::list<ArkanoidJoint *> _joints;
  void setBody(float32 x, float32 y, float32 width, float32 height,
               float32 anchorX, float32 limit, b2World &world);
  bool _sticky;
  function<void()> _action;
  ACTIONS _actionType;

 public:
  Paddle(){};
  Paddle(float32 x, float32 y, float32 width, float32 height, float32 anchorX,
         float32 limit, float32 maxSpeed, ACTIONS action, Texture *texture);
  ~Paddle();
  virtual void update();
  virtual void afterUpdate();
  virtual void render() const;
  virtual void handleEvents(SDL_Event event);
  virtual void onBeginContact(RigidBody *rigigbody);
  virtual void setWidth(float32 width);
  void jointTo(Ball *ball);
  void splitFromBalls();
  void setSticky(bool sticky) { _sticky = sticky; };
  virtual std::istream &deserialize(std::istream &out);
  virtual std::ostream &serialize(std::ostream &is) const;
  void setAction(ACTIONS action);
};
