#include "ShortenAward.h"
#include "Game.h"
#include "GameState.h"

/// Public
/// Constructor
ShortenAward::ShortenAward(float32 x, float32 y, float32 width, float32 height, float32 speed, uint framerate, Texture *texture)
    : Award(x, y, width, height, speed, framerate, texture) {}

/// Public Virtual
/// Defines behaviour when the instance gets in contact with the instance
void ShortenAward::contact()
{
  // Call the default behaviour
  Award::contact();

  // Creates an event that makes the paddle shorter
  State::current->addEvent([]() { dynamic_cast<GameState *>(State::current)->paddle()->setWidth(ArkanoidSettings::paddleMinimumWidth); });
}
