#include "CollisionLogic.h"
#include "RigidBody.h"

void CollisionLogic::BeginContact(b2Contact* contact) {
  const auto a = contact->GetFixtureA()->GetBody()->GetUserData();
  const auto b = contact->GetFixtureB()->GetBody()->GetUserData();
  if (a && b && a != b) {
    auto bodyUserDataA = static_cast<RigidBody*>(a);
    auto bodyUserDataB = static_cast<RigidBody*>(b);

    bodyUserDataA->onBeginContact(bodyUserDataB);
    bodyUserDataB->onBeginContact(bodyUserDataA);
  }
}

void CollisionLogic::EndContact(b2Contact* contact) {
  const auto a = contact->GetFixtureA()->GetBody()->GetUserData();
  const auto b = contact->GetFixtureB()->GetBody()->GetUserData();
  if (a && b && a != b) {
    auto bodyUserDataA = static_cast<RigidBody*>(a);
    auto bodyUserDataB = static_cast<RigidBody*>(b);

    bodyUserDataA->onEndContact(bodyUserDataB);
    bodyUserDataB->onEndContact(bodyUserDataA);
  }
}
