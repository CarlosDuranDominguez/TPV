#pragma once

#include "checkML.h"
#include "Text.h"

class Timer : public Text
{
private:
  int time;

public:
  Timer(float x, float y, int width, int height, SDL_Color color, Font *font);
  ~Timer(){};
  void update();
  virtual std::istream &deserialize(std::istream &out);
  virtual std::ostream &serialize(std::ostream &is) const;
};
