#pragma once

#include "Text.h"

class ScoreMarker final : public Text {
  int score_;

 public:
  ScoreMarker(float32 x, float32 y, float32 width, float32 height,
              SDL_Color color, Font *font);
  ~ScoreMarker();
  void update() override;
  std::istream &deserialize(std::istream &out) override;
  std::ostream &serialize(std::ostream &is) const override;
};
