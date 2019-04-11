#include "ArkanoidTimer.h"

ArkanoidTimer::ArkanoidTimer() {
  firstTime_ = new time_t();
  time(firstTime_);
}

ArkanoidTimer::~ArkanoidTimer() { delete firstTime_; }

float ArkanoidTimer::getSeconds() const {
  time_t now;
  time(&now);
  return (float)difftime(now, *firstTime_);
}

void ArkanoidTimer::delay(Uint32 time) { *firstTime_ -= time; }

void ArkanoidTimer::reset() { time(firstTime_); }
