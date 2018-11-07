#include "GameManager.h"
#include "Game.h"
#include "LoadManager.h"

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
void GameManager::finishLevel(double time)
{
	_totalTime += time;
	if (_currentLevel != 2)
		_currentLevel++;
	else
		_game->newScore("Alguien", 1000 - time, time);
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
	_totalTime = 0.0;
}
