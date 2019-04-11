#pragma once
#include <Box2D/Box2D.h>

class CollisionLogic final : public b2ContactListener {
  void BeginContact(b2Contact* contact);
  void EndContact(b2Contact* contact);
};
