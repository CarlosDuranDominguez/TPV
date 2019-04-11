#include "StickyAward.h"
#include "ArkanoidSettings.h"
#include "Game.h"
#include "State.h"

StickyAward::StickyAward() = default;
StickyAward::StickyAward(const float32 x, const float32 y, const float32 width,
                         const float32 height, const float32 speed,
                         const Uint32 framerate, Texture* texture)
    : Award(x, y, width, height, speed, framerate, texture) {}

// Defines behaviour when the instance gets in contact with the instance
void StickyAward::contact() {
  // Call the default behaviour
  Award::contact();

  // Creates an event that skips to the next level
  State::current_->addEvent([]() {
    auto pad = reinterpret_cast<GameState*>(State::current_)->paddle();
    pad->setWidth(ArkanoidSettings::paddleWidth_);
    pad->setAction(STICKY);
  });
}
