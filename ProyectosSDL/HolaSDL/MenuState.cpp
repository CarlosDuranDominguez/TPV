#include "MenuState.h"
#include <functional>
#include "Button.h"
#include "Game.h"

/// Public
// Constructor
MenuState::MenuState(Game *game, SDL_Renderer *renderer)
    : State(game, renderer) {
  // Create 4 buttons with their names and callbacks
  auto _buttons = new Button *[4];
  string nombres[4] = {"New Game", "Continue", "ScoreBoard", "Exit"};
  function<void()> callbacks[4] = {[this, game]() {
                                     exit_ = true;
                                     game->changeState(GAME);
                                     game->getGameManager()->setLevel(1);
                                   },
                                   [this, game]() {
                                     exit_ = true;
                                     game->changeState(GAME);
                                     game->getGameManager()->setLevel(0);
                                   },
                                   [this, game]() {
                                     exit_ = true;
                                     game->changeState(SCOREBOARD);
                                   },
                                   [this, game]() {
                                     exit_ = true;
                                     game->changeState(GAMEOVER);
                                   }};

  for (int i = 0; i < 4; i++) {
    _buttons[i] =
        new Button(game->getFonts()[BIG_FONT], 0.0f, i * 110.0f, 200.0f, 100.0f,
                   kWhite, kGrey, nombres[i], callbacks[i]);
    add(*_buttons[i]);
  }

  // Delete the temporary array
  delete[] _buttons;
}

MenuState::~MenuState() {}
