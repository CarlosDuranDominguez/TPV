#include "MultiBallAward.h"
#include "Game.h"
#include "GameState.h"
#include "State.h"

MultiBallAward::MultiBallAward() = default;

// Constructor
MultiBallAward::MultiBallAward(const float32 x, const float32 y,
                               const float32 width, const float32 height,
                               const float32 speed, const Uint32 frameRate,
                               Texture *texture)
    : Award(x, y, width, height, speed, frameRate, texture) {}

// Defines behaviour when the instance gets in contact with the instance
void MultiBallAward::contact() {
  // Call the default behaviour
  Award::contact();

  // Creates an event that creates two new balls
  State::current_->addEvent([this]() {
    auto gs = reinterpret_cast<GameState *>(State::current_);
    auto pos = dynamic_cast<RigidBody *>(this)->getPosition();
    pos.y -= 10;
    pos.x -= 5.0f;
    reinterpret_cast<RigidBody *>(gs->create(kBall, pos))
        ->setVelocity(b2Vec2{1000, -1000});
    pos.x += 10.0f;
    reinterpret_cast<RigidBody *>(gs->create(kBall, pos))
        ->setVelocity(b2Vec2{-1000, -1000});
  });
}
