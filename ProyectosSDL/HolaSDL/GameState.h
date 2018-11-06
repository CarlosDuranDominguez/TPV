#pragma once

#include "Texture.h"
#include "Timer.h"
#include "Ball.h"
#include "Paddle.h"
#include "BlocksMap.h"
#include "Wall.h"

class Game;

class GameState
{
private:
	SDL_Renderer *_renderer = nullptr;
	bool _exit = false, _gameover = false, _win = false;
	Game *_game;
	Timer *_timer;
	Ball *_ball = nullptr;
	Paddle *_paddle = nullptr;
	BlocksMap *_blocksmap = nullptr;
	Wall *_upWall = nullptr, *_rightWall = nullptr, *_leftWall = nullptr;
	void _render() const;
	void _update();
	void _handleevents();
	

public:
	GameState(Game *game, SDL_Renderer *renderer);
	~GameState();
	void init();
	void run();
	bool collides(const Ball *, Vector2D &, Vector2D &) const;
	
};
