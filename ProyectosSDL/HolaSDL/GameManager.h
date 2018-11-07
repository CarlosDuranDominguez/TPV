#pragma once

class Game;

class GameManager
{
private:
	int _currentLevel;
	double _totalTime;
	Game* _game;
public:
	GameManager(Game* game);
	void finishLevel(double time);
	int level();
	void setLevel(int);
	void reset();
};
