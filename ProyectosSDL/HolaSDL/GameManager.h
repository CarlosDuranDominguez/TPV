#pragma once

#include "checkML.h"
#include "Box2D/Box2D.h"

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
	Game *_game;

  public:
	GameManager(Game *game);
	void finishLevel(float32 time);
	int level();
	void setLevel(int);
	void reset();
	void setBlocks(int blocksLenght);
	void addBlock();
	void deleteBlock();
	void addScore(int score);
	int getScore() const;
	void setBalls(int ballsLenght);
	void deleteBall();
	void addBalls(int balls);
	void setLives(int livesLenght);
	void deleteLive();
	void addLives(int lives);
	int getLives() const;
	void newGame();
};
