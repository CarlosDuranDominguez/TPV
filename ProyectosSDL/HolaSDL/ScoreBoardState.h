#pragma once
#include "ScoreBoard.h"
#include "Button.h"

class Game;

class ScoreBoardState
{
private:
	ScoreBoard *scoreboard;
	Button *button;
	Game *game;
	SDL_Renderer *renderer;
	bool exit = false;
	void render();
	void handleEvents();

public:
	ScoreBoardState(Game *game, SDL_Renderer *renderer);
	~ScoreBoardState();
	void run();
};
