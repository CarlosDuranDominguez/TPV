#pragma once

#include "GameObject.h"
#include "Renderable.h"
#include "Texture.h"
#include "Updatable.h"

class ArkanoidObject : public GameObject, public Renderable, public Updatable {
 protected:
  uint textureIndex() const;
  Texture *readTexture(std::istream &out);

 public:
  ArkanoidObject(){};
  ArkanoidObject(float32 x, float32 y, float32 width, float32 height,
                 Texture *texture)
      : GameObject(x, y, width, height), Renderable(texture), Updatable(){};
  ~ArkanoidObject(){};
  virtual void render() const;
  virtual void update() = 0;
  virtual std::istream &deserialize(std::istream &out) = 0;
  virtual std::ostream &serialize(std::ostream &is) const = 0;
};
