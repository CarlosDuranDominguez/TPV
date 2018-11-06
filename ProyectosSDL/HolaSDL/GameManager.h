#pragma once

class GameManager 
{
private:
	int _currentLevel;
	double _totalTime;
public:
	GameManager();
	void finishLevel(double time);
	int level();
	void reset();
};