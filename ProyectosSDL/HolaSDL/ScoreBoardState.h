#pragma once
#include "Game.h"
#include "ScoreBoard.h"
#include "Button.h"

class ScoreBoardState {
private:
	ScoreBoard* scoreboard;
	Button* button;
	bool exit = false;
	void render();
	void handleEvents();
public:
	ScoreBoardState(Game* game);
	~ScoreBoardState();
	void run(); 
};