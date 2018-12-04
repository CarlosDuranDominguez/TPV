#pragma once
#include "State.h"
#include "Paddle.h"

class GameState : public State {
protected:
	virtual void _end();
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
	void loadLevel(const string& path);
	void saveLevel(const string& path);
	Paddle* paddle() { return dynamic_cast<Paddle*>(**(_paddles.begin())); };
};