#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include "Font.h"
#include "Text.h"
#include "checkML.h"

class ScoreBoard : public GameObject, public Renderable {
 private:
  Font *_font;
  Text *_texts[10];
  SDL_Color _color;

 public:
  ScoreBoard(Font *font, float32 x, float32 y, float32 width, float32 height,
             SDL_Color color);
  ~ScoreBoard();
  void rewrite();
  virtual void render() const;
  std::istream &deserialize(std::istream &out);
  std::ostream &serialize(std::ostream &is) const;
};
