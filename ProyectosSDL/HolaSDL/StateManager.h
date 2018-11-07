#pragma once

#include "checkML.h"
#include <string>
#include "GameState.h"
#include "MenuState.h"
#include "ScoreBoardState.h"

using namespace std;

class StateManager
{
private:
	GameState *game;
	MenuState *menu;
	ScoreBoardState *scoreboard;
	string _currentState;

public:
	StateManager(GameState *game, MenuState *menu, ScoreBoardState *scoreboard);
	~StateManager();
	void run();
	void changeState(const string &nameState);
	string currentState() const;
};
