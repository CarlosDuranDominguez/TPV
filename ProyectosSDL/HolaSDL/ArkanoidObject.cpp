#pragma once

#include"ArkanoidObject.h"
#include "GameManager.h"
#include "Game.h"

void ArkanoidObject::render() const {
	_texture->render(SDL_Rect{
	  (int)getPosition().x,
	  (int)getPosition().y,
	  (int)getSize().x,
	  (int)getSize().y });
}

// Protected
// Retrieves the texture's index for this ArkanoidObject
// for serializing purposes
uint ArkanoidObject::textureIndex() const {
  auto game = GameManager::getGame();
  auto textures = game->getTextures();
  uint i = 0;
  while (i < NUMBER_TEXTURES && _texture != textures[i]) i++;
  return i;
}