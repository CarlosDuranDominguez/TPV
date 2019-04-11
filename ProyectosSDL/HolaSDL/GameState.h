#pragma once
#include "Paddle.h"
#include "State.h"

class GameState final : public State {
 protected:
  void _end() override;
  Paddle* paddle_;
  void _reset();

 private:
  void _destroyAll();

 public:
  GameState(Game* game, SDL_Renderer* renderer);
  ~GameState();
  void reset() override;
  void init() override;
  void loadLevel(const string& path);
  void saveLevel(const string& path);
  Paddle* paddle() const;
};
