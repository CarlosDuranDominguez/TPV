#include "CollisionLogic.h"
#include "RigidBody.h"

void CollisionLogic::BeginContact(b2Contact* contact) {
  void* a = contact->GetFixtureA()->GetBody()->GetUserData();
  void* b = contact->GetFixtureB()->GetBody()->GetUserData();
  if (a && b && a != b) {
    RigidBody* bodyUserDataA = static_cast<RigidBody*>(a);
    RigidBody* bodyUserDataB = static_cast<RigidBody*>(b);

    bodyUserDataA->onBeginContact(bodyUserDataB);
    bodyUserDataB->onBeginContact(bodyUserDataA);
  }
}

void CollisionLogic::EndContact(b2Contact* contact) {
  void* a = contact->GetFixtureA()->GetBody()->GetUserData();
  void* b = contact->GetFixtureB()->GetBody()->GetUserData();
  if (a && b && a != b) {
    RigidBody* bodyUserDataA = static_cast<RigidBody*>(a);
    RigidBody* bodyUserDataB = static_cast<RigidBody*>(b);

    bodyUserDataA->onEndContact(bodyUserDataB);
    bodyUserDataB->onEndContact(bodyUserDataA);
  }
}
