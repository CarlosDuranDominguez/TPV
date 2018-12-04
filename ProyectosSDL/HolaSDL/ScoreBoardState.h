#pragma once

#include "checkML.h"
#include "ScoreBoard.h"
#include "Button.h"
#include "State.h"

class Game;

class ScoreBoardState : public State
{
private:
  ScoreBoard *_scoreboard;

public:
  ScoreBoardState(Game *game, SDL_Renderer *renderer);
  ~ScoreBoardState();
  void pushNewFinishGame(const string &name, int score, int time);
};
