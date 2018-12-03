#include "GameManager.h"
#include "Game.h"
#include "LoadManager.h"
#include "GameState.h"

/**
 * Constructor.
 */
GameManager::GameManager(Game *game)
	: _game(game)
{
	reset();
};

/**
 * Finishes the level and pushes to leaderboard.
 */
void GameManager::finishLevel(float32 time)
{
	_totalTime += time;
	if (_currentLevel != 2)
		_currentLevel++;
	else
		_game->newScore("Alguien", _score, time);
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
	_currentLevel = 0;
	_currentBlocks = 0;
	_currentBalls = 0;
	_score = 0;
	_totalTime = 0.0;
	_lives = 0;
}

void GameManager::setBlocks(int blocksLenght) {
	_currentBlocks = blocksLenght;
}

void GameManager::addBlock() {
	++_currentBlocks;
}

void GameManager::deleteBlock() {
	if (--_currentBlocks == 0) {
		finishLevel(static_cast<GameState*>(State::current)->getTime());
	}
}

void GameManager::addScore(int score) {
	_score += score;
}

void GameManager::setBalls(int ballsLenght) {
	_currentBalls = ballsLenght;
}

void GameManager::deleteBall(){
	if (--_currentBalls == 0) {
		deleteLive();
	}
}

void GameManager::addBalls(int balls){
	_currentBalls += balls;
}

void GameManager::setLives(int livesLenght) {
	_lives = livesLenght;
}

void GameManager::deleteLive() {
	if (--_lives == 0) {
 		_game->changeState(States::MENU);
	}
	else {
		State::current->reset();
	}
}

void GameManager::addLives(int lives){
	_lives += lives;
}

void GameManager::newGame() {
	reset();
	_currentLevel = 0;
}
