#pragma once

#include "Box2D/Box2D.h"
#include "TopBoard.h"
#include "checkML.h"

class Game;

class GameManager {
 private:
  int _currentLevel;
  float32 _totalTime;
  int _currentBlocks;
  int _currentBalls;
  int _score;
  int _lives;
  static Game *_game;
  TopBoard *_topBoard;

 public:
  GameManager(Game *game);
  ~GameManager();
  int getLevel() const { return _currentLevel; };
  int getLives() const { return _lives; };
  int getScore() const { return _score; };
  int getTotalTime() const { return _totalTime; };
  TopBoard *getTopBoard() const { return _topBoard; };
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
  static Game *getGame() { return _game; };
  static void setGame(Game *game) { _game = game; };
  std::vector<PlayerGame *> getScores() const {
    return _topBoard->showScores();
  };
};
