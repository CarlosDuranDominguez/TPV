#include "EnlargenAward.h"
#include "ArkanoidSettings.h"
#include "Game.h"
#include "GameState.h"

EnlargenAward::EnlargenAward() = default;

EnlargenAward::EnlargenAward(const float32 x, const float32 y,
                             const float32 width, const float32 height,
                             const float32 speed, const Uint32 frameRate,
                             Texture* texture)
    : Award(x, y, width, height, speed, frameRate, texture) {}

// Defines behaviour when the instance gets in contact with the instance
void EnlargenAward::contact() {
  // Call the default behaviour
  Award::contact();

  // Creates an event that makes the paddle larger
  State::current_->addEvent([]() {
    auto pad = reinterpret_cast<GameState*>(State::current_)->paddle();
    pad->setWidth(ArkanoidSettings::paddleMaximumWidth_);
    pad->setAction(NONE);
  });
}
