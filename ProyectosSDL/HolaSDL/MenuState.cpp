#include "MenuState.h"
#include "ScoreBoardState.h"
#include "Button.h"
#include "Game.h"
#include <functional>

/// Public
// Constructor
MenuState::MenuState(Game *game, SDL_Renderer *renderer) : State(game, renderer)
{
  // Create 4 buttons with their names and callbacks
  auto _buttons = new Button *[4];
  string nombres[4] = {"New Game", "Continue", "ScoreBoard", "Exit"};
  function<void()> callbacks[4] = {
      [this, game]() { _exit = true; game->pushState(*new GameState(game, game->getRenderer())); game->getGameManager()->setLevel(1); },
      [this, game]() { _exit = true; game->pushState(*new GameState(game, game->getRenderer())); game->getGameManager()->setLevel(0); },
	  [this, game]() { _exit = true; game->pushState(*new ScoreBoardState(game, game->getRenderer())); },
      [this, game]() { _exit = true; game->popState(); }};

  for (int i = 0; i < 4; i++)
  {
    _buttons[i] = new Button(game->getFonts()[BIGFONT], 0.0f, i * 110.0f, 200.0f, 100.0f, WHITE, GREY, nombres[i], callbacks[i]);
    add(*_buttons[i]);
  }

  // Delete the temporary array
  delete[] _buttons;
}
