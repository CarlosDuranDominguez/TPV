#pragma once

#include "checkML.h"
#include <string>
#include "GameState.h"
#include "MenuState.h"
#include "ScoreBoardState.h"

using namespace std;

enum States
{
	GAMEOVER,
	SCOREBOARD,
	GAME,
	MENU
};

class StateManager
{
private:
	GameState *game;
	MenuState *menu;
	ScoreBoardState *scoreboard;
	States _currentState;

public:
	StateManager(GameState *game, MenuState *menu, ScoreBoardState *scoreboard);
	~StateManager();
	void run();
	void changeState(const States &state);
	States currentState() const;
};
