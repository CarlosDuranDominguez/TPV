#pragma once

#include "checkML.h"
#include "Box2D/Box2D.h"
#include "TopBoard.h"

class Game;


class GameManager
{
private:
  int _currentLevel;
  float32 _totalTime;
  int _currentBlocks;
  int _currentBalls;
  int _score;
  int _lives;
  static Game *_game;
  TopBoard* _topBoard;

public:
  GameManager(Game *game);
  ~GameManager();
  int getLevel() const { return _currentLevel; };
  int getLives() const { return _lives; };
  int getScore() const { return _score; };
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
  void setBalls(int ballsLenght);
  void setBlocks(int blocksLenght);
  void setLevel(int level);
  void setLives(int livesLenght);
  void setScore(int score);
  static Game *getGame() { return _game; };
  static void setGame(Game *game) { _game = game; };
  std::vector<PlayerGame*> getScores() const { return _topBoard->showScores(); };
};
