#include "GameManager.h"
#include "ArkanoidSettings.h"
#include "Game.h"
#include "GameState.h"

// Constructor
GameManager::GameManager(Game* game) {
  setGame(game);
  topBoard_ = new TopBoard("../saves/save.save");
  newGame();
};

Game* GameManager::game_ = nullptr;

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

// Add an amount of balls to the game manager
void GameManager::addBalls(const int balls) { currentBalls_ += balls; }

// Add a block to the game manager
void GameManager::addBlock() { ++currentBlocks_; }

// Add an amount of lives to the game manager
void GameManager::addLives(const int lives) { lives_ += lives; }

// Add an amount of points to the game manager
void GameManager::addScore(const int score) { score_ += score; }

// Remove a ball from the game manager
void GameManager::deleteBall() {
  // If there are no remaining balls, remove a life
  if (--currentBalls_ == 0) deleteLive();
}

// Remove a block from the game manager
void GameManager::deleteBlock() {
  // If there are no blocks, finish the level
  if (--currentBlocks_ == 0)
    finishLevel(reinterpret_cast<GameState*>(State::current_)->getTime());
}

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

// Finishes the level and pushes to leaderboard
void GameManager::finishLevel(const float32 time) {
  totalTime_ += time;
  // We store _currentLevel as int instead of Uint32 because it causes compiler
  // errors
  if (Uint32(currentLevel_) < ArkanoidSettings::totalLevels_) {
    currentLevel_++;
    State::current_->end();
  } else {
    topBoard_->pushScore(new PlayerGame{"Somebody", score_, int(totalTime_)});
    game_->changeState(States::SCOREBOARD);
  }
}

// Creates a new game, resetting the game manager's properties
void GameManager::newGame() {
  reset();
  currentLevel_ = 1;
  score_ = 0;
  totalTime_ = 0.0;
  lives_ = ArkanoidSettings::initialLives_;
}

// Reset this game manager's amount of blocks and balls
void GameManager::reset() {
  currentBlocks_ = 0;
  currentBalls_ = 0;
}

// Set this game manager's amount of balls
void GameManager::setBalls(const int balls) { currentBalls_ = balls; }

// Set this game manager's amount of blocks
void GameManager::setBlocks(const int blocks) { currentBlocks_ = blocks; }

// Set the game manager's current level
void GameManager::setLevel(const int level) { currentLevel_ = level; }

// Set the game manager's amount of lives
void GameManager::setLives(const int lives) { lives_ = lives; }

// Set the game manager's amount of points
void GameManager::setScore(const int score) { score_ = score; }

// Set the game manager's total time
void GameManager::setTotalTime(const float32 time) { totalTime_ = time; }
