#pragma once
#include "ArkanoidBody.h"

class Wall final : public ArkanoidBody {
  void setBody(float32 x, float32 y, float32 width, float32 height,
               b2World &world);

 public:
  Wall();
  Wall(float32 x, float32 y, float32 width, float32 height, Texture *texture);
  ~Wall();
  void update() override;
  void render() const override;
  std::istream &deserialize(std::istream &out) override;
  std::ostream &serialize(std::ostream &is) const override;
};
