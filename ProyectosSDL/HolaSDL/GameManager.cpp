#include "GameManager.h"
#include "Game.h"

GameManager::GameManager(Game* game) : _game(game) {  reset(); };

void GameManager::finishLevel(double time) {
	_totalTime += time;
	if (_currentLevel != 2)
		_currentLevel++;
	else
		_game->newScore("Alguien", 1000 - time, time);
}
int GameManager::level() {
	return _currentLevel;
}
void GameManager::reset() {
	_currentLevel = 0;
	_totalTime = 0.0;
}