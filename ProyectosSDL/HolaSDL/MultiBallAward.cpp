#include "MultiBallAward.h"
#include "Game.h"
#include "State.h"
#include "GameState.h"

/// Public
/// Constructor
MultiBallAward::MultiBallAward(float32 x, float32 y, float32 width, float32 height, float32 speed, float32 framerate, Texture *texture)
    : Award(x, y, width, height, speed, framerate, texture) {}

/// Public Virtual
/// Defines behaviour when the instance gets in contact with the instance
void MultiBallAward::contact()
{
  // Call the default behaviour
  Award::contact();

  // Creates an event that creates two new balls
  State::current->addEvent([this]() {
    GameState *gs = dynamic_cast<GameState *>(State::current);
    b2Vec2 pos = dynamic_cast<RigidBody *>(this)->getPosition();
    pos.y -= 10;
    pos.x -= 5.0f;
    dynamic_cast<RigidBody *>(gs->create(ball, pos))->setVelocity(b2Vec2{1000, -1000});
    pos.x += 10.0f;
    dynamic_cast<RigidBody *>(gs->create(ball, pos))->setVelocity(b2Vec2{-1000, -1000});
  });
}
