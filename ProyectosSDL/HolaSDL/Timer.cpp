#include "Timer.h"
#include <math.h>
#include "State.h"

/**
 * Constructors.
 */
Timer::Timer(float x, float y, int width, int height, SDL_Color color, Font *font)
    : Text(font, x, y, width, height, color, "HOLA")
{
  time = State::current->getTime();
  setText(to_string(time));
};

/// Public Victual
/// Updates the update behaviour
void Timer::update()
{
  if (time != State::current->getTime())
  {
    time = State::current->getTime();
    setText(to_string(time));
  }
}

/// Public Virtual
/// Defines the deserialize method behaviour to patch the instance when loading a file save
std::istream &Timer::deserialize(std::istream &out)
{
  return out;
}

/// Public Virtual
/// Defines the serialize method behaviour to save the data into a file save
std::ostream &Timer::serialize(std::ostream &is) const
{
  return is;
}
