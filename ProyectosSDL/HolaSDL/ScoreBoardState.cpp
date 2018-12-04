#include "ScoreBoardState.h"
#include "Game.h"

/**
 * Constructor.
 */
ScoreBoardState::ScoreBoardState(Game *game, SDL_Renderer *renderer)
    : State(game, renderer)
{
  GameObject *gameObject;
  gameObject = _scoreboard = new ScoreBoard(game->getFonts()[MEDIUMFONT], 0, 0, 200, 40, WHITE, "../saves/save.save");
  add(*gameObject);
  gameObject = new Button(game->getFonts()[0], 0, 400, 200, 100, WHITE, GREY, "Exit", [this, game]() {
    _exit = true;
    game->changeState(MENU);
  });
  add(*gameObject);
}

/**
 * Destructor.
 */
ScoreBoardState::~ScoreBoardState()
{
}

/**
 * It put a new game in the record.
 */
void ScoreBoardState::pushNewFinishGame(const string &name, int score, int time)
{
  _scoreboard->pushGame({name, score, time});
}
