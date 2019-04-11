#pragma once

#include "Button.h"
#include "SDL.h"
#include "State.h"
#include "checkML.h"

class Game;

const unsigned int NUMBER_BUTTONS_MENU = 3;

class MenuState : public State {
 public:
  MenuState(Game *game, SDL_Renderer *renderer);
  ~MenuState(){};
};
