#include "StateManager.h"

/*
 * Constructor.
 */
StateManager::StateManager(GameState *game, MenuState *menu, ScoreBoardState *scoreboard)
	: game(game), menu(menu), scoreboard(scoreboard)
{
	_currentState = "menu";
}

/*
 * Destructor.
 */
StateManager::~StateManager()
{
}

/*
 * Executes the loop of the selected state or exit.
 */
void StateManager::run()
{
	while (_currentState != "gameover")
	{
		if (_currentState == "menu")
		{
			menu->run();
		}
		else if (_currentState == "game")
		{
			game->init();
			game->run();
		}
		else if (_currentState == "scoreboard")
		{
			scoreboard->run();
		}
	}
}

/*
 * It changes the current state(exit form the current state is necesary).
 */
void StateManager::changeState(const string &nameState)
{
	if (nameState != "gameover" && nameState != "menu" && nameState != "game" && nameState != "scoreboard")
	{
		throw "Non existing state";
	}
	else
	{
		_currentState = nameState;
	}
}

/*
 * It gets the name of the current state.
 */
string StateManager::currentState() const
{
	return _currentState;
}
