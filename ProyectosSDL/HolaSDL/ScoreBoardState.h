#pragma once
#include "ScoreBoard.h"
#include "State.h"

class Game;

class ScoreBoardState final : public State {
  ScoreBoard *scoreboard_;

 public:
  ScoreBoardState(Game *game, SDL_Renderer *renderer);
  ~ScoreBoardState();
  void init() override;
};
