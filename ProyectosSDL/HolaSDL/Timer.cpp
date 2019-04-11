#include "Timer.h"
#include "State.h"

/// Public
// Constructor
Timer::Timer(float32 x, float32 y, float32 width, float32 height,
             SDL_Color color, Font *font)
    : Text(font, x, y, width, height, color, "") {
  time_ = (int)State::current_->getTime();
  setText(to_string(time_));
}

Timer::~Timer() {
}

/// Public Virtual
// Updates the update behaviour
void Timer::update() {
  auto now = (int)State::current_->getTime();
  if (time_ != now) {
    time_ = now;
    setText(to_string(time_));
  }
}

/// Public Virtual
// Defines the deserialize method behaviour to patch the instance when loading a
// file save
std::istream &Timer::deserialize(std::istream &out) { return out; }

/// Public Virtual
// Defines the serialize method behaviour to save the data into a file save
std::ostream &Timer::serialize(std::ostream &is) const { return is; }
