#include "EnlargenAward.h"
#include "ArkanoidSettings.h"
#include "Game.h"
#include "GameState.h"

EnlargenAward::EnlargenAward() {}  /// Public Virtual
EnlargenAward::EnlargenAward(float32 x, float32 y, float32 width,
                             float32 height, float32 speed, Uint32 frameRate,
                             Texture* texture)
    : Award(x, y, width, height, speed, frameRate, texture) {
}  // Defines behaviour when the instance gets in contact with the instance
void EnlargenAward::contact() {
  // Call the default behaviour
  Award::contact();

  // Creates an event that makes the paddle larger
  State::current_->addEvent([]() {
    Paddle* pad = dynamic_cast<GameState*>(State::current_)->paddle();
    pad->setWidth(ArkanoidSettings::paddleMaximumWidth_);
    pad->setAction(NONE);
  });
}
