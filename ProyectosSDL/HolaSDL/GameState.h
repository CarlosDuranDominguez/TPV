#pragma once
#include "State.h"

class GameState : public State {
protected:
	virtual void _end();
	b2Timer *timer;
	list<list<GameObject*>::iterator> _paddles;
	list<list<GameObject*>::iterator> _balls;
	virtual void _destroy();
	void _reset();
private:
	bool _isReseting;
public:
	GameState(Game *game, SDL_Renderer *renderer);
	virtual ~GameState();
	virtual void reset();
	virtual void init();
	float32 getTime();
};