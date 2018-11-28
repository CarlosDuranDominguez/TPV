#pragma once
#include "State.h"

class GameState : public State {
protected:
	virtual void _end();
public:
	GameState(Game *game, SDL_Renderer *renderer) :State(game, renderer) {}
	virtual void init();
};