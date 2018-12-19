#pragma once
#include "State.h"
#include "Paddle.h"

class GameState : public State
{
protected:
  virtual void _end();
  Paddle *_paddle;
  void _reset();

private:
  void _destroyAll();

public:
  GameState(Game *game, SDL_Renderer *renderer)
	  : State(game, renderer) {
	  init();
  };
  virtual ~GameState(){};
  virtual void reset();
  virtual void init();
  void loadLevel(const string &path);
  void saveLevel(const string &path);
  Paddle *paddle() { return _paddle; };
};
