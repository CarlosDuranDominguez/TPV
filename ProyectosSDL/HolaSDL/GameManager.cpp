#include "GameManager.h"
#include "ArkanoidSettings.h"
#include "Game.h"
#include "GameState.h"

/// Public
// Constructor
GameManager::GameManager(Game* game) {
  setGame(game);
  topBoard_ = new TopBoard("../saves/save.save");
  newGame();
};

Game* GameManager::game_ = nullptr;

/// Public
// Destructor
GameManager::~GameManager() {
  topBoard_->storeFile("../saves/save.save");
  delete topBoard_;
}

int GameManager::getLevel() const { return currentLevel_; }

int GameManager::getLives() const { return lives_; }

int GameManager::getScore() const { return score_; }

int GameManager::getTotalTime() const {
  return static_cast<int>(floor(totalTime_));
}

TopBoard* GameManager::getTopBoard() const { return topBoard_; }

Game* GameManager::getGame() { return game_; }

void GameManager::setGame(Game* game) { game_ = game; }

std::vector<PlayerGame*> GameManager::getScores() const {
  return topBoard_->showScores();
};

/// Public
// Add an amount of balls to the game manager
void GameManager::addBalls(int balls) { currentBalls_ += balls; }

/// Public
// Add a block to the game manager
void GameManager::addBlock() { ++currentBlocks_; }

/// Public
// Add an amount of lives to the game manager
void GameManager::addLives(int lives) { lives_ += lives; }

/// Public
// Add an amount of points to the game manager
void GameManager::addScore(int score) { score_ += score; }

/// Public
// Remove a ball from the game manager
void GameManager::deleteBall() {
  // If there are no remaining balls, remove a life
  if (--currentBalls_ == 0) deleteLive();
}

/// Public
// Remove a block from the game manager
void GameManager::deleteBlock() {
  // If there are no blocks, finish the level
  if (--currentBlocks_ == 0)
    finishLevel(static_cast<GameState*>(State::current_)->getTime());
}

/// Public
// Removes a life from the game manager
void GameManager::deleteLive() {
  // If there are no lives left, go to the menu and end the current state
  if (--lives_ == 0) {
    game_->changeState(States::MENU);
    State::current_->end();
  } else {
    // Or reset the state if there are enough lives to continue playing
    State::current_->reset();
  }
}

/// Public
// Finishes the level and pushes to leaderboard
void GameManager::finishLevel(float32 time) {
  totalTime_ += time;
  // We store _currentLevel as int instead of Uint32 because it causes compiler
  // errors
  if ((Uint32)currentLevel_ < ArkanoidSettings::totalLevels_) {
    currentLevel_++;
    State::current_->end();
  } else {
    topBoard_->pushScore(new PlayerGame{"Alguien", score_, (int)totalTime_});
    game_->changeState(States::SCOREBOARD);
  }
}

/// Public
// Creates a new game, resetting the game manager's properties
void GameManager::newGame() {
  reset();
  currentLevel_ = 1;
  score_ = 0;
  totalTime_ = 0.0;
  lives_ = ArkanoidSettings::initialLives_;
}

/// Public
// Reset this game manager's amount of blocks and balls
void GameManager::reset() {
  currentBlocks_ = 0;
  currentBalls_ = 0;
}

/// Public
// Set this game manager's amount of balls
void GameManager::setBalls(int balls) { currentBalls_ = balls; }

/// Public
// Set this game manager's amount of blocks
void GameManager::setBlocks(int blocks) { currentBlocks_ = blocks; }

/// Public
// Set the game manager's current level
void GameManager::setLevel(int level) { currentLevel_ = level; }

/// Public
// Set the game manager's amount of lives
void GameManager::setLives(int lives) { lives_ = lives; }

/// Public
// Set the game manager's amount of points
void GameManager::setScore(int score) { score_ = score; }

/// Public
// Set the game manager's total time
void GameManager::setTotalTime(float32 time) { totalTime_ = time; }
