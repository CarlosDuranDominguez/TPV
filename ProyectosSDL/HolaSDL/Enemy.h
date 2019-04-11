#pragma once
#include "ArkanoidBody.h"

class Game;

class Enemy final : public ArkanoidBody {
  float32 speed_;
  float32 halfLife_;
  float32 changeProbability_;
  float32 framerate_;
  b2Timer *timer_;
  b2Timer *animationTimer_;
  Uint32 frame_;
  void setBody(float32 x, float32 y, float32 radius, b2World &world);

 public:
  Enemy();
  Enemy(float32 x, float32 y, float32 width, float32 height, float32 maxSpeed,
        float32 halfLife, float32 changeProbability, float32 framerate,
        Texture *texture);
  ~Enemy();
  void update() override;
  void onBeginContact(RigidBody *rigidBody) override;
  void render() const override;
  void setPosition(float32 x, float32 y) override;
  std::istream &deserialize(std::istream &out) override;
  std::ostream &serialize(std::ostream &is) const override;
};
