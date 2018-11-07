#include "GameManager.h"
#include "Game.h"
#include "LoadManager.h"

GameManager::GameManager(Game *game)
	: _game(game)
{
	reset();
};

void GameManager::finishLevel(double time)
{
	_totalTime += time;
	if (_currentLevel != 2)
		_currentLevel++;
	else
		_game->newScore("Alguien", 1000 - time, time);
}

void GameManager::setLevel(int level)
{
	_currentLevel = level;
}

int GameManager::level()
{
	return _currentLevel;
}

void GameManager::reset()
{
	_currentLevel = 0;
	_totalTime = 0.0;
}
