#pragma once

#include "checkML.h"
#include "SDL.h"
#include "Button.h"
#include "State.h"

class Game;

const unsigned int NUMBER_BUTTONS_MENU = 3;

class MenuState : public State
{
public:
  MenuState(Game *game, SDL_Renderer *renderer);
  ~MenuState();
};
