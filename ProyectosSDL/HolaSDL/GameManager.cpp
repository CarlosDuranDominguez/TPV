#include "GameManager.h"
#include "Game.h"
#include "GameState.h"

/// Public
// Constructor
GameManager::GameManager(Game *game) {
  GameManager::setGame(game);
  _topBoard = new TopBoard("../saves/save.save");
  newGame();
};

Game *GameManager::_game = nullptr;

/// Public
// Destructor
GameManager::~GameManager() {
  _topBoard->storeFile("../saves/save.save");
  delete _topBoard;
};

/// Public
// Add an amount of balls to the game manager
void GameManager::addBalls(int balls) { _currentBalls += balls; }

/// Public
// Add a block to the game manager
void GameManager::addBlock() { ++_currentBlocks; }

/// Public
// Add an amount of lives to the game manager
void GameManager::addLives(int lives) { _lives += lives; }

/// Public
// Add an amount of points to the game manager
void GameManager::addScore(int score) { _score += score; }

/// Public
// Remove a ball from the game manager
void GameManager::deleteBall() {
  // If there are no remaining balls, remove a life
  if (--_currentBalls == 0) deleteLive();
}

/// Public
// Remove a block from the game manager
void GameManager::deleteBlock() {
  // If there are no blocks, finish the level
  if (--_currentBlocks == 0)
    finishLevel(static_cast<GameState *>(State::current)->getTime());
}

/// Public
// Removes a life from the game manager
void GameManager::deleteLive() {
  // If there are no lives left, go to the menu and end the current state
  if (--_lives == 0) {
    _game->changeState(States::MENU);
    State::current->end();
  } else {
    // Or reset the state if there are enough lives to continue playing
    State::current->reset();
  }
}

/// Public
// Finishes the level and pushes to leaderboard
void GameManager::finishLevel(float32 time) {
  _totalTime += time;
  // We store _currentLevel as int instead of uint because it causes compiler
  // errors
  if ((uint)_currentLevel < ArkanoidSettings::totalLevels) {
    _currentLevel++;
    State::current->end();
  } else {
    _topBoard->pushScore(new PlayerGame{"Alguien", _score, (int)_totalTime});
    _game->changeState(States::SCOREBOARD);
  }
}

/// Public
// Creates a new game, resetting the game manager's properties
void GameManager::newGame() {
  reset();
  _currentLevel = 1;
  _score = 0;
  _totalTime = 0.0;
  _lives = ArkanoidSettings::initialLives;
}

/// Public
// Reset this game manager's amount of blocks and balls
void GameManager::reset() {
  _currentBlocks = 0;
  _currentBalls = 0;
}

/// Public
// Set this game manager's amount of balls
void GameManager::setBalls(int balls) { _currentBalls = balls; }

/// Public
// Set this game manager's amount of blocks
void GameManager::setBlocks(int blocks) { _currentBlocks = blocks; }

/// Public
// Set the game manager's current level
void GameManager::setLevel(int level) { _currentLevel = level; }

/// Public
// Set the game manager's amount of lives
void GameManager::setLives(int lives) { _lives = lives; }

/// Public
// Set the game manager's amount of points
void GameManager::setScore(int score) { _score = score; }

/// Public
// Set the game manager's total time
void GameManager::setTotalTime(float32 time) { _totalTime = time; }
