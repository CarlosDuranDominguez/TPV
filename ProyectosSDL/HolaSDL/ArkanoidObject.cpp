#pragma once

#include "ArkanoidObject.h"
#include "FileFormatError.h"
#include "Game.h"
#include "GameManager.h"

/// Public Virtual
// Defines the render behaviour
void ArkanoidObject::render() const {
  texture_->render(SDL_Rect{(int)getPosition().x, (int)getPosition().y,
                            (int)getSize().x, (int)getSize().y});
}

/// Protected
// Retrieves the texture's index for this ArkanoidObject
// for serializing purposes
Uint32 ArkanoidObject::textureIndex() const {
  auto game = GameManager::getGame();
  auto textures = game->getTextures();
  Uint32 i = 0;
  while (i < kNumberTextures && texture_ != textures[i]) i++;
  return i;
}

/// Protected
// Sets the texture
Texture *ArkanoidObject::readTexture(std::istream &out) {
  Uint32 i;
  out >> i;

  if (i < 0 || i >= kNumberTextures)
    throw new FileFormatError("Invalid texture index " + i);
  return GameManager::getGame()->getTextures()[i];
}

ArkanoidObject::ArkanoidObject() {
}

ArkanoidObject::
ArkanoidObject(float32 x, float32 y, float32 width, float32 height, Texture* texture): GameObject(x, y, width, height),
                                                                                       Renderable(texture),
                                                                                       Updatable() {
}

ArkanoidObject::~ArkanoidObject() {
}
