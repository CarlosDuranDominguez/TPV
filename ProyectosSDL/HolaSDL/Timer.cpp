#include "Timer.h"
#include "State.h"

// Constructor
Timer::Timer(const float32 x, const float32 y, const float32 width,
             const float32 height, const SDL_Color color, Font *font)
    : Text(font, x, y, width, height, color, "") {
  time_ = int(State::current_->getTime());
  setText(to_string(time_));
}

Timer::~Timer() = default;

// Updates the update behaviour
void Timer::update() {
  const auto now = int(State::current_->getTime());
  if (time_ != now) {
    time_ = now;
    setText(to_string(time_));
  }
}

// Defines the deserialize method behaviour to patch the instance when loading a
// file save
std::istream &Timer::deserialize(std::istream &out) { return out; }

// Defines the serialize method behaviour to save the data into a file save
std::ostream &Timer::serialize(std::ostream &is) const { return is; }
