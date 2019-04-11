#pragma once

#include "ArkanoidBody.h"

class Award : public ArkanoidBody {
  Uint32 frameRate_;
  Uint32 frame_;
  Uint32 animationTimer_;
  float32 speed_;
  bool contacted_;
  void setBody(float32 x, float32 y, float32 width, float32 height,
               b2World &world);

 public:
  Award();;
  Award(float32 x, float32 y, float32 width, float32 height, float32 speed,
      Uint32 frameRate, Texture *texture);
  ~Award();
  virtual void update();
  virtual void render() const;
  virtual void contact();
  virtual void destroy();
  virtual void afterUpdate();
  virtual void onBeginContact(RigidBody *rigidbody);
  virtual std::istream &deserialize(std::istream &out);
  virtual std::ostream &serialize(std::ostream &is) const;
  int getFramerate() const;;
};
