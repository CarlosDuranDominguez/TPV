#include "ShortenAward.h"
#include "Game.h"
#include "GameState.h"

/// Public Virtual
// Defines behaviour when the instance gets in contact with the instance
void ShortenAward::contact() {
  // Call the default behaviour
  Award::contact();

  // Creates an event that makes the paddle shorter
  State::current->addEvent([]() {
    Paddle* pad = dynamic_cast<GameState*>(State::current)->paddle();
    pad->setWidth(ArkanoidSettings::paddleMinimumWidth);
    pad->setAction(NONE);
  });
}
