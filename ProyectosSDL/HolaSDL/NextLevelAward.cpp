#include "NextLevelAward.h"
#include "Game.h"

NextLevelAward::NextLevelAward() = default;

// Constructor
NextLevelAward::NextLevelAward(const float32 x, const float32 y,
                               const float32 width, const float32 height,
                               const float32 speed, const Uint32 frameRate,
                               Texture *texture)
    : Award(x, y, width, height, speed, frameRate, texture) {}

// Defines behaviour when the instance gets in contact with the instance
void NextLevelAward::contact() {
  // Call the default behaviour
  Award::contact();

  // Creates an event that skips to the next level
  State::current_->addEvent([]() {
    Game::getGameManager()->finishLevel(State::current_->getTime());
  });
}
