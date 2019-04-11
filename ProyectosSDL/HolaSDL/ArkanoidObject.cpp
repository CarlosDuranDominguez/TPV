#include "ArkanoidObject.h"
#include "FileFormatError.h"
#include "Game.h"
#include "GameManager.h"

ArkanoidObject::ArkanoidObject() = default;

ArkanoidObject::ArkanoidObject(const float32 x, const float32 y,
                               const float32 width, const float32 height,
                               Texture *texture)
    : GameObject(x, y, width, height), Renderable(texture), Updatable() {}

ArkanoidObject::~ArkanoidObject() = default;

// Defines the render behaviour
void ArkanoidObject::render() const {
  texture_->render(SDL_Rect{int(getPosition().x), int(getPosition().y),
                            int(getSize().x), int(getSize().y)});
}

// Retrieves the texture's index for this ArkanoidObject
// for serializing purposes
Uint32 ArkanoidObject::textureIndex() const {
  auto game = GameManager::getGame();
  const auto textures = game->getTextures();
  Uint32 i = 0;
  while (i < kNumberTextures && texture_ != textures[i]) i++;
  return i;
}

// Sets the texture
Texture *ArkanoidObject::readTexture(std::istream &out) {
  Uint32 i;
  out >> i;

  if (i < 0 || i >= kNumberTextures)
    throw FileFormatError("Invalid texture index " + to_string(i));
  return GameManager::getGame()->getTextures()[i];
}
