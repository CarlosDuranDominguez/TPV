#include "ScoreBoardState.h"
#include "Button.h"
#include "Game.h"

// Constructor
ScoreBoardState::ScoreBoardState(Game *game, SDL_Renderer *renderer)
    : State(game, renderer) {
  GameObject *gameObject = scoreboard_ =
      new ScoreBoard(game->getFonts()[MEDIUM_FONT], 0, 0, 200, 40, kWhite);
  add(*gameObject);
  gameObject = new Button(game->getFonts()[0], 0, 400, 200, 100, kWhite, kGrey,
                          "Exit", [this, game]() {
                            exit_ = true;
                            game->changeState(MENU);
                          });
  add(*gameObject);
  gameObject = new Button(game->getFonts()[0], 200, 400, 200, 100, kWhite,
                          kGrey, "By Time", [this, game]() {
                            Game::getGameManager()->getTopBoard()->sortByTime();
                            this->scoreboard_->rewrite();
                          });
  add(*gameObject);
  gameObject = new Button(game->getFonts()[0], 400, 400, 200, 100, kWhite,
                          kGrey, "By Name", [this, game]() {
                            Game::getGameManager()->getTopBoard()->sortByName();
                            this->scoreboard_->rewrite();
                          });
  add(*gameObject);
  gameObject =
      new Button(game->getFonts()[0], 600, 400, 200, 100, kWhite, kGrey,
                 "By Score", [this, game]() {
                   Game::getGameManager()->getTopBoard()->sortByScore();
                   this->scoreboard_->rewrite();
                 });
  add(*gameObject);
}

ScoreBoardState::~ScoreBoardState() = default;

void ScoreBoardState::init() {
  State::init();
  scoreboard_->rewrite();
}
