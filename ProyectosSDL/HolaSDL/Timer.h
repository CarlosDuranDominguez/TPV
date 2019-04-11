#pragma once

#include "Text.h"
#include "checkML.h"

class Timer : public Text {
 private:
  int time;

 public:
  Timer(float32 x, float32 y, float32 width, float32 height, SDL_Color color,
        Font *font);
  ~Timer(){};
  void update();
  virtual std::istream &deserialize(std::istream &out);
  virtual std::ostream &serialize(std::ostream &is) const;
};
