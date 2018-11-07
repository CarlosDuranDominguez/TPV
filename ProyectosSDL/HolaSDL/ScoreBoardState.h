#pragma once

#include "checkML.h"
#include "ScoreBoard.h"
#include "Button.h"

class Game;

class ScoreBoardState
{
private:
	ScoreBoard *_scoreboard;
	Button *_button;
	Game *_game;
	SDL_Renderer *_renderer;
	bool _exit = false;
	void _render();
	void _handleEvents();

public:
	ScoreBoardState(Game *game, SDL_Renderer *renderer);
	~ScoreBoardState();
	void run();
	void pushNewFinishGame(const string& name, int score, int time);
};
