#include "LaserAward.h"
#include "Game.h"
#include "State.h"
#include "Bullet.h"

/// Public
/// Constructor
LaserAward::LaserAward(float32 x, float32 y, float32 width, float32 height, float32 speed, uint framerate, Texture *texture)
    : Award(x, y, width, height, speed, framerate, texture) {}

/// Public Virtual
/// Defines behaviour when the instance gets in contact with the instance
void LaserAward::contact()
{
  // Call the default behaviour
  Award::contact();

  // Creates an event that makes the paddle shorter
  State::current->addEvent([]() {
    Paddle *pad = dynamic_cast<GameState *>(State::current)->paddle();
    pad->setAction([pad]() {
      State::current->addEvent([pad]() {
        /*Create Bullet*/
        Bullet *bullet = new Bullet(pad->getPosition().x, pad->getPosition().y, 10.0f, 1000.0f, Game::current->getTextures()[BALLBLACK]);
        State::current->add(*bullet);
        bullet->setVelocity(b2Vec2{0, -1000.0f});
      });
    });
  });
}
