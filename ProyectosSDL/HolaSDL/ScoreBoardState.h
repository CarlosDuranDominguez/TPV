#pragma once

#include "Button.h"
#include "ScoreBoard.h"
#include "State.h"
#include "checkML.h"

class Game;

class ScoreBoardState : public State {
 private:
  ScoreBoard *_scoreboard;

 public:
  ScoreBoardState(Game *game, SDL_Renderer *renderer);
  ~ScoreBoardState(){};
  virtual void init();
};
