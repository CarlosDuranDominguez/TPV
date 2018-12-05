#include "ScoreBoardState.h"
#include "Game.h"

/// Public
/// Constructor
ScoreBoardState::ScoreBoardState(Game *game, SDL_Renderer *renderer)
    : State(game, renderer)
{
  GameObject *gameObject;
  gameObject = _scoreboard = new ScoreBoard(game->getFonts()[MEDIUMFONT], 0, 0, 200, 40, WHITE);
  add(*gameObject);
  gameObject = new Button(game->getFonts()[0], 0, 400, 200, 100, WHITE, GREY, "Exit", [this, game]() {
    _exit = true;
    game->changeState(MENU);
  });
  add(*gameObject);
}

void ScoreBoardState::init() {
	State::init();
	_scoreboard->rewrite();
}
