#include "MenuState.h"
#include <functional>
#include "Button.h"
#include "Game.h"
#include "GameStateMachine.h"
#include "ScoreBoardState.h"

// Constructor
MenuState::MenuState(Game *game, SDL_Renderer *renderer)
    : State(game, renderer) {
  auto y = 0;
  add(*new Button(game->getFonts()[BIG_FONT], 0.0f, y++ * 110.0f, 200.0f,
                  100.0f, kWhite, kGrey, "New Game", [this, game]() {
                    game->getGameStateMachine()->pushState(
                        new GameState(game_, renderer_));
                    Game::getGameManager()->setLevel(1);
                  }));
  add(*new Button(game->getFonts()[BIG_FONT], 0.0f, y++ * 110.0f, 200.0f,
                  100.0f, kWhite, kGrey, "Continue", [this, game]() {
                    game->getGameStateMachine()->pushState(
                        new GameState(game_, renderer_));
                    Game::getGameManager()->setLevel(0);
                  }));
  add(*new Button(game->getFonts()[BIG_FONT], 0.0f, y++ * 110.0f, 200.0f,
                  100.0f, kWhite, kGrey, "ScoreBoard", [this, game]() {
                    game->getGameStateMachine()->pushState(
                        new ScoreBoardState(game_, renderer_));
                  }));
  add(*new Button(game->getFonts()[BIG_FONT], 0.0f, y++ * 110.0f, 200.0f,
                  100.0f, kWhite, kGrey, "Exit", [this, game]() {
                    addEvent([this]() { game_->flushStates(); });
                  }));
}

MenuState::~MenuState() = default;
