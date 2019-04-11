#pragma once

#include "Box2D/Box2D.h"
#include "TopBoard.h"

class Game;

class GameManager {
  int currentLevel_;
  float32 totalTime_;
  int currentBlocks_;
  int currentBalls_;
  int score_;
  int lives_;
  static Game *game_;
  TopBoard *topBoard_;

 public:
  explicit GameManager(Game *game);
  ~GameManager();
  int getLevel() const;
  int getLives() const;
  int getScore() const;
  int getTotalTime() const;
  TopBoard *getTopBoard() const;
  void addBalls(int balls);
  void addBlock();
  void addLives(int lives);
  void addScore(int score);
  void deleteBall();
  void deleteBlock();
  void deleteLive();
  void finishLevel(float32 time);
  void newGame();
  void reset();
  void setBalls(int balls);
  void setBlocks(int blocks);
  void setLevel(int level);
  void setLives(int lives);
  void setScore(int score);
  void setTotalTime(float32 time);
  static Game *getGame();
  static void setGame(Game *game);
  std::vector<PlayerGame *> getScores() const;
};
