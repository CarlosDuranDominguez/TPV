#pragma once
#include <list>
#include "ArkanoidBody.h"
#include "Ball.h"
#include "Controllable.h"
#include "functional"

class Game;
enum Actions { NONE, BEGIN, STICKY, LASER };
class Paddle final : public ArkanoidBody, public Controllable {
  class ArkanoidJoint {
   public:
    ArkanoidJoint(Ball *ball, b2Vec2 &distance);
    ~ArkanoidJoint();
    b2Vec2 distance_;
    Ball *ball_;
  };

  bool rightMovement_, leftMovement_;
  float32 speed_;
  float32 leftAnchor_, rightAnchor_;
  std::list<ArkanoidJoint *> joints_;
  void setBody(float32 x, float32 y, float32 width, float32 height,
               float32 anchorX, float32 limit, b2World &world);
  bool sticky_;
  function<void()> action_;
  Actions actionType_;

 public:
  Paddle();
  Paddle(float32 x, float32 y, float32 width, float32 height, float32 anchorX,
         float32 limit, float32 maxSpeed, Actions action, Texture *texture);
  ~Paddle();
  void update() override;
  void afterUpdate() override;
  void render() const override;
  void handleEvents(SDL_Event event) override;
  void onBeginContact(RigidBody *rigigBody) override;
  void setWidth(float32 width);
  void jointTo(Ball *ball);
  void splitFromBalls();
  void setSticky(bool sticky);
  ;
  std::istream &deserialize(std::istream &out) override;
  std::ostream &serialize(std::ostream &is) const override;
  void setAction(Actions action);
};
