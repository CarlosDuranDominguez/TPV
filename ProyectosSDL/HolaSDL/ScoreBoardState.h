#pragma once
#include "ScoreBoard.h"
#include "Button.h"

class Game;

class ScoreBoardState {
private:
	ScoreBoard* scoreboard;
	Button* button;
	Game* game;
	bool exit = false;
	void render();
	void handleEvents();
public:
	ScoreBoardState(Game* game);
	~ScoreBoardState();
	void run(); 
};