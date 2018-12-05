#include "GameManager.h"
#include "Game.h"
#include "GameState.h"

/// Public
/// Constructor
GameManager::GameManager(Game *game)
{
  GameManager::setGame(game);
  _topBoard = new TopBoard("../saves/save.save");
  reset();
};

Game *GameManager::_game = nullptr;

/// Public
/// Destructor
GameManager::~GameManager() {
	_topBoard->storeFile("../saves/save.save");
	delete _topBoard;
}
/**
 * Finishes the level and pushes to leaderboard.
 */
void GameManager::finishLevel(float32 time)
{
  _totalTime += time;
  if (_currentLevel < ArkanoidSettings::totalLevels)
  {
	  _currentLevel++;
	  State::current->end();
  }
  else
  {
	  _topBoard->pushScore(new PlayerGame{ "Alguien", _score, (int)_totalTime });
	  _game->changeState(States::SCOREBOARD);
  }
}

/**
 * Set level.
 */
void GameManager::setLevel(int level)
{
  _currentLevel = level;
}

/**
 * Get the level.
 */
int GameManager::level()
{
  return _currentLevel;
}

/**
 * Reset the level and time.
 */
void GameManager::reset()
{
  _currentBlocks = 0;
  _currentBalls = 0;
}

void GameManager::setBlocks(int blocksLenght)
{
  _currentBlocks = blocksLenght;
}

void GameManager::addBlock()
{
  ++_currentBlocks;
}

void GameManager::deleteBlock()
{
  if (--_currentBlocks == 0)
  {
    finishLevel(static_cast<GameState *>(State::current)->getTime());
  }
}

void GameManager::addScore(int score)
{
  _score += score;
}

int GameManager::getScore() const
{
  return _score;
}

void GameManager::setScore(int score)
{
  _score = score;
}

void GameManager::setBalls(int ballsLenght)
{
  _currentBalls = ballsLenght;
}

void GameManager::deleteBall()
{
  if (--_currentBalls == 0)
  {
    deleteLive();
  }
}

void GameManager::addBalls(int balls)
{
  _currentBalls += balls;
}

void GameManager::setLives(int livesLenght)
{
  _lives = livesLenght;
}

void GameManager::deleteLive()
{
  if (--_lives == 0)
  {
    _game->changeState(States::MENU);
	State::current->end();
  }
  else
  {
    State::current->reset();
  }
}

void GameManager::addLives(int lives)
{
  _lives += lives;
}

int GameManager::getLives() const
{
  return _lives;
}

void GameManager::newGame()
{
  reset();
  _currentLevel = 0;
  _score = 0;
  _totalTime = 0.0;
  _lives = ArkanoidSettings::initialLives;
}
