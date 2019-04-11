#pragma once

#include "SDL.h"
#include "State.h"

class Game;

const unsigned int kNumberButtonsMenu = 3;

class MenuState final : public State {
 public:
  MenuState(Game *game, SDL_Renderer *renderer);
  ~MenuState();
};
