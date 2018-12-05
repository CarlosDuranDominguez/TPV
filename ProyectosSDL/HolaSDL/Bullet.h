#include "Ball.h"

class Bullet : public Ball
{
private:
  virtual void setBody(float32 x, float32 y, float32 radius, b2World &world);

public:
  Bullet(){};
  Bullet(float32 x, float32 y, float32 radius, float32 speed, Texture *texture);
  ~Bullet(){};
  virtual void onBeginContact(RigidBody *rigidBody);
  virtual std::istream &deserialize(std::istream &out);
  virtual std::ostream &serialize(std::ostream &is) const;
};
