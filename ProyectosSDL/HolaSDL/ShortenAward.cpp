#include "ShortenAward.h"
#include "ArkanoidSettings.h"
#include "Game.h"
#include "GameState.h"

ShortenAward::ShortenAward() {}
ShortenAward::ShortenAward(float32 x, float32 y, float32 width, float32 height,
                           float32 speed, Uint32 framerate, Texture* texture)
    : Award(x, y, width, height, speed, framerate, texture) {}

/// Public
// Defines behaviour when the instance gets in contact with the instance
void ShortenAward::contact() {
  // Call the default behaviour
  Award::contact();

  // Creates an event that makes the paddle shorter
  State::current_->addEvent([]() {
    Paddle* pad = dynamic_cast<GameState*>(State::current_)->paddle();
    pad->setWidth(ArkanoidSettings::paddleMinimumWidth_);
    pad->setAction(NONE);
  });
}
