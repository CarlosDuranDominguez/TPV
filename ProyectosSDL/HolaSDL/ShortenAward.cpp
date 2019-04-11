#include "ShortenAward.h"
#include "ArkanoidSettings.h"
#include "Game.h"
#include "GameState.h"

ShortenAward::ShortenAward() = default;
ShortenAward::ShortenAward(const float32 x, float32 y, const float32 width,
                           const float32 height, const float32 speed,
                           const Uint32 framerate, Texture* texture)
    : Award(x, y, width, height, speed, framerate, texture) {}

// Defines behaviour when the instance gets in contact with the instance
void ShortenAward::contact() {
  // Call the default behaviour
  Award::contact();

  // Creates an event that makes the paddle shorter
  State::current_->addEvent([]() {
    auto pad = reinterpret_cast<GameState*>(State::current_)->paddle();
    pad->setWidth(ArkanoidSettings::paddleMinimumWidth_);
    pad->setAction(NONE);
  });
}
