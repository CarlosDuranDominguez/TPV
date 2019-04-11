#include "StickyAward.h"
#include "ArkanoidSettings.h"
#include "Game.h"
#include "State.h"

StickyAward::StickyAward() {}
StickyAward::StickyAward(float32 x, float32 y, float32 width, float32 height,
                         float32 speed, Uint32 framerate, Texture* texture)
    : Award(x, y, width, height, speed, framerate, texture) {}

/// Public
// Defines behaviour when the instance gets in contact with the instance
void StickyAward::contact() {
  // Call the default behaviour
  Award::contact();

  // Creates an event that skips to the next level
  State::current_->addEvent([]() {
    Paddle* pad = dynamic_cast<GameState*>(State::current_)->paddle();
    pad->setWidth(ArkanoidSettings::paddleWidth_);
    pad->setAction(STICKY);
  });
}
