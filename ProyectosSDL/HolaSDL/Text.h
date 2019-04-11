#pragma once

#include "Font.h"
#include "GameObject.h"
#include "Renderable.h"

class Text : public GameObject, public Renderable {
 private:
  Font *_font;
  Texture *_texture;
  string _text;
  SDL_Color _color;
  int _width, _height;

 public:
  Text(Font *font, float32 x, float32 y, float32 width, float32 height,
       const SDL_Color &color, const string &text);
  ~Text();
  void setText(const string newText);
  SDL_Rect getRect() const;
  SDL_Color setColor(const SDL_Color &color);
  void render() const;
  virtual std::istream &deserialize(std::istream &out);
  virtual std::ostream &serialize(std::ostream &is) const;
};
