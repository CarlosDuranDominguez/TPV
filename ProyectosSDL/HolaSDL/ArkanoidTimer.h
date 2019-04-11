#include <ctime>
#include "SDL.h"

class ArkanoidTimer {
 private:
  time_t *_firstTime;

 public:
  ArkanoidTimer() {
    _firstTime = new time_t();
    time(_firstTime);
  }
  ~ArkanoidTimer() { delete _firstTime; }
  float32 getSeconds() const {
    time_t now;
    time(&now);
    return (float32)difftime(now, *_firstTime);
  }
  void delay(Uint32 time) { *_firstTime -= time; }
  void reset() { time(_firstTime); }
};
