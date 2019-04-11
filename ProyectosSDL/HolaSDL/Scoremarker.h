#pragma once

#include "Text.h"
#include "checkML.h"

class ScoreMarker : public Text {
 private:
  int _score;

 public:
  ScoreMarker(float32 x, float32 y, float32 width, float32 height,
              SDL_Color color, Font *font);
  ~ScoreMarker(){};
  void update();
  virtual std::istream &deserialize(std::istream &out);
  virtual std::ostream &serialize(std::ostream &is) const;
};
