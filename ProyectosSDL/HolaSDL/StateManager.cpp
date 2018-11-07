#include "StateManager.h"

/**
 * Constructor.
 */
StateManager::StateManager(GameState *game, MenuState *menu, ScoreBoardState *scoreboard)
	: game(game), menu(menu), scoreboard(scoreboard)
{
	_currentState = MENU;
}

/**
 * Destructor.
 */
StateManager::~StateManager()
{
}

/**
 * Executes the loop of the selected state or exit.
 */
void StateManager::run()
{
	while (_currentState != GAMEOVER)
	{
		if (_currentState == MENU)
		{
			menu->run();
		}
		else if (_currentState == GAME)
		{
			game->init();
			game->run();
		}
		else if (_currentState == SCOREBOARD)
		{
			scoreboard->run();
		}
	}
}

/**
 * It changes the current state(exit form the current state is necesary).
 */
void StateManager::changeState(const States &state)
{
	_currentState = state;
}

/**
 * It gets the name of the current state.
 */
States StateManager::currentState() const
{
	return _currentState;
}
