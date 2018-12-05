#include "NextLevelAward.h"
#include "Game.h"
#include "GameState.h"

/// Public
/// Constructor
NextLevelAward::NextLevelAward(float32 x, float32 y, float32 width, float32 height, float32 speed, uint framerate, Texture *texture)
    : Award(x, y, width, height, speed, framerate, texture) {}

/// Public Virtual
/// Defines behaviour when the instance gets in contact with the instance
void NextLevelAward::contact()
{
  // Call the default behaviour
  Award::contact();

  // Creates an event that skips to the next level
  State::current->addEvent([]() { Game::gameManager()->finishLevel(State::current->getTime()); });
}
