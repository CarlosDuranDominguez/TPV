#pragma once

#include "checkML.h"
#include "ArkanoidObject.h"
#include "RigidBody.h"

class Award : public ArkanoidObject, public RigidBody
{
private:
  int _framerate;
  uint _frame;
  b2Timer *_animationTimer;
  bool _contacted;
  void setBody(float32 x, float32 y, float32 width, float32 height, b2World &world);

public:
  Award(){};
  Award(float32 x, float32 y, float32 width, float32 height, float32 framerate, Texture *texture);
  ~Award();
  virtual void update();
  virtual void render() const;
  virtual void contact();
  virtual void destroy();
  virtual void onBeginContact(RigidBody *rigidbody);
  virtual std::istream &deserialize(std::istream &out);
  virtual std::ostream &serialize(std::ostream &is) const;
  int getFramerate() const { return _framerate; };
};
