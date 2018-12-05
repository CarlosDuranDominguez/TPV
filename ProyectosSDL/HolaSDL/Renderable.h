#pragma once

#include "Texture.h"

/*
 *Renderable interface
 */
class Renderable
{
protected:
  Texture *_texture;

public:
  Renderable(){};
  Renderable(Texture *texture) : _texture(texture){};
  ~Renderable(){};
  virtual void render() const {};
};
