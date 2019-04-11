#pragma once

#include <string>
#include "Font.h"
#include "Text.h"

class ScoreBoard final : public GameObject, public Renderable {
  Font *font_;
  Text *texts_[10];
  SDL_Color color_;

 public:
  ScoreBoard(Font *font, float32 x, float32 y, float32 width, float32 height,
             SDL_Color color);
  ~ScoreBoard();
  void rewrite();
  void render() const override;
  std::istream &deserialize(std::istream &out) override;
  std::ostream &serialize(std::ostream &is) const override;
};
