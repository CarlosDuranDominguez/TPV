#include "StateManager.h"

StateManager::StateManager(GameState* game, MenuState* menu, ScoreBoardState* scoreboard): game(game), menu(menu),scoreboard(scoreboard) {
	 _currentState = "menu";
 }

StateManager::~StateManager() {
}

void StateManager::run() {
	while (_currentState != "gameover") {
		if (_currentState == "menu") {
			menu->run();
		}
		else if (_currentState == "game") {
			game->run();
		}
		else if (_currentState == "scoreboard") {
			scoreboard->run();
		}
	}
}
void StateManager::changeState(const string& nameState) {
	if (nameState != "gameover" && nameState != "menu" && nameState != "game" && nameState != "scoreboard") {
		throw "Non existing state";
	}
	else {
		_currentState = nameState;
	}

}
string StateManager::currentState() const {
	return _currentState;
}