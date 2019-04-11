#include <Box2D/Box2D.h>
#include "RigidBody.h"

class CollisionLogic : public b2ContactListener {
  void BeginContact(b2Contact *contact) {
    void *a = contact->GetFixtureA()->GetBody()->GetUserData();
    void *b = contact->GetFixtureB()->GetBody()->GetUserData();
    if (a && b && a != b) {
      RigidBody *bodyUserDataA = static_cast<RigidBody *>(a);
      RigidBody *bodyUserDataB = static_cast<RigidBody *>(b);

      bodyUserDataA->onBeginContact(bodyUserDataB);
      bodyUserDataB->onBeginContact(bodyUserDataA);
    }
  }

  void EndContact(b2Contact *contact) {
    void *a = contact->GetFixtureA()->GetBody()->GetUserData();
    void *b = contact->GetFixtureB()->GetBody()->GetUserData();
    if (a && b && a != b) {
      RigidBody *bodyUserDataA = static_cast<RigidBody *>(a);
      RigidBody *bodyUserDataB = static_cast<RigidBody *>(b);

      bodyUserDataA->onEndContact(bodyUserDataB);
      bodyUserDataB->onEndContact(bodyUserDataA);
    }
  }
};
