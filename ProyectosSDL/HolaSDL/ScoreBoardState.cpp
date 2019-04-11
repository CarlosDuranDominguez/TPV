#include "ScoreBoardState.h"
#include "Button.h"
#include "Game.h"
#include "GameStateMachine.h"

// Constructor
ScoreBoardState::ScoreBoardState(Game *game, SDL_Renderer *renderer)
    : State(game, renderer) {
  GameObject *gameObject = scoreboard_ =
      new ScoreBoard(game->getFonts()[MEDIUM_FONT], 0, 0, 200, 40, kWhite);
  add(*gameObject);
  gameObject = new Button(
      game->getFonts()[0], 0, 400, 200, 100, kWhite, kGrey, "Exit", [this]() {
        addEvent([this]() { game_->getGameStateMachine()->popState(); });
      });
  add(*gameObject);
  gameObject = new Button(game->getFonts()[0], 200, 400, 200, 100, kWhite,
                          kGrey, "By Time", [this]() {
                            Game::getGameManager()->getTopBoard()->sortByTime();
                            scoreboard_->rewrite();
                          });
  add(*gameObject);
  gameObject = new Button(game->getFonts()[0], 400, 400, 200, 100, kWhite,
                          kGrey, "By Name", [this]() {
                            Game::getGameManager()->getTopBoard()->sortByName();
                            scoreboard_->rewrite();
                          });
  add(*gameObject);
  gameObject =
      new Button(game->getFonts()[0], 600, 400, 200, 100, kWhite, kGrey,
                 "By Score", [this]() {
                   Game::getGameManager()->getTopBoard()->sortByScore();
                   scoreboard_->rewrite();
                 });
  add(*gameObject);
}

ScoreBoardState::~ScoreBoardState() = default;

void ScoreBoardState::init() {
  State::init();
  scoreboard_->rewrite();
}
