#include "StickyAward.h"
#include "Game.h"
#include "State.h"

/// Public Virtual
// Defines behaviour when the instance gets in contact with the instance
void StickyAward::contact()
{
  // Call the default behaviour
  Award::contact();

  // Creates an event that skips to the next level
  State::current->addEvent([]() {
	  Paddle* pad = dynamic_cast<GameState *>(State::current)->paddle();
	  pad->setWidth(ArkanoidSettings::paddleWidth);
	  pad->setAction(STICKY);
  });
}
