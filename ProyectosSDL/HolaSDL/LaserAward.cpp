#include "LaserAward.h"
#include "ArkanoidSettings.h"
#include "Game.h"
#include "State.h"

LaserAward::LaserAward() {}

/// Public
// Constructor
LaserAward::LaserAward(float32 x, float32 y, float32 width, float32 height,
                       float32 speed, Uint32 frameRate, Texture *texture)
    : Award(x, y, width, height, speed, frameRate, texture) {}

/// Public Virtual
// Defines behaviour when the instance gets in contact with the instance
void LaserAward::contact() {
  // Call the default behaviour
  Award::contact();

  // Creates an event that makes the paddle shorter
  State::current_->addEvent([]() {
    Paddle *pad = dynamic_cast<GameState *>(State::current_)->paddle();
    pad->setWidth(ArkanoidSettings::paddleWidth_);
    pad->setAction(LASER);
  });
}
