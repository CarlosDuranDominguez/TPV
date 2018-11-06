#pragma once

#include "Texture.h"
#include "Timer.h"
#include "Ball.h"
#include "Paddle.h"
#include "BlocksMap.h"
#include "Wall.h"

class Game;

class GameState {
private:
	SDL_Renderer* renderer = nullptr;
	bool exit = false, gameover = false, win = false;
	Game* game;
	Timer* timer;
	Ball* ball = nullptr;
	Paddle* paddle = nullptr;
	BlocksMap* blocksmap = nullptr;
	Wall *upWall = nullptr, *rightWall = nullptr, *leftWall = nullptr;
public:
	GameState( Game* game, SDL_Renderer*  renderer);
	~GameState();
	void init();
	void run();
	void render() const;
	void update();
	void handleEvents();
	bool collides(const Ball*, Vector2D&, Vector2D&);
};