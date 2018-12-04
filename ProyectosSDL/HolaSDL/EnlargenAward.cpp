#include "EnlargenAward.h"
#include "Game.h"
#include "GameState.h"

EnlargenAward::EnlargenAward(float32 x, float32 y, float32 width, float32 height, float32 speed, float32 framerate, Texture *texture)
    : Award(x, y, width, height, speed, framerate, texture) {}

/// Public Virtual
/// Defines behaviour when the instance gets in contact with the instance
void EnlargenAward::contact()
{
  // Call the default behaviour
  Award::contact();

  // Creates an event that makes the paddle larger
  State::current->addEvent([]() { dynamic_cast<GameState *>(State::current)->paddle()->setWidth(200); });
}
