#pragma once

#include "Texture.h"

/*
 * Renderable interface
 */
class Renderable {
 protected:
  Texture* texture_;

 public:
  Renderable();
  Renderable(Texture* texture);
  virtual ~Renderable();
  virtual void render() const = 0;
};

inline Renderable::Renderable() {}

inline Renderable::Renderable(Texture* texture) : texture_(texture) {}

inline Renderable::~Renderable() {}
