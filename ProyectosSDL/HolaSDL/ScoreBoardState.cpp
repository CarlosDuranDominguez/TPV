#include "ScoreBoardState.h"
#include "Game.h"

/// Public
// Constructor
ScoreBoardState::ScoreBoardState(Game *game, SDL_Renderer *renderer)
    : State(game, renderer) {
  GameObject *gameObject;
  gameObject = _scoreboard =
      new ScoreBoard(game->getFonts()[MEDIUMFONT], 0, 0, 200, 40, WHITE);
  add(*gameObject);
  gameObject = new Button(game->getFonts()[0], 0, 400, 200, 100, WHITE, GREY,
                          "Exit", [this, game]() {
                            _exit = true;
                            game->changeState(MENU);
                          });
  add(*gameObject);
  gameObject = new Button(game->getFonts()[0], 200, 400, 200, 100, WHITE, GREY,
                          "By Time", [this, game]() {
                            Game::getGameManager()->getTopBoard()->sortByTime();
                            this->_scoreboard->rewrite();
                          });
  add(*gameObject);
  gameObject = new Button(game->getFonts()[0], 400, 400, 200, 100, WHITE, GREY,
                          "By Name", [this, game]() {
                            Game::getGameManager()->getTopBoard()->sortByName();
                            this->_scoreboard->rewrite();
                          });
  add(*gameObject);
  gameObject =
      new Button(game->getFonts()[0], 600, 400, 200, 100, WHITE, GREY,
                 "By Score", [this, game]() {
                   Game::getGameManager()->getTopBoard()->sortByScore();
                   this->_scoreboard->rewrite();
                 });
  add(*gameObject);
}

void ScoreBoardState::init() {
  State::init();
  _scoreboard->rewrite();
}
