#include "ScoreBoardState.h"
#include "Game.h"

ScoreBoardState::ScoreBoardState(Game *game, SDL_Renderer *renderer) : _game(game), _renderer(renderer)
{
	_scoreboard = new ScoreBoard(game->getFonts()[0], 0, 0, 200, 40, WHITE, "../saves/save.save");
	_button = new Button(game->getFonts()[0], 0, 400, 200, 100, WHITE, GREY, "Exit", [this, game]() {
		_exit = true;
		game->changeState("menu");
	});
}

ScoreBoardState::~ScoreBoardState()
{
	delete _scoreboard;
	delete _button;
}

void ScoreBoardState::run()
{
	_exit = false;
	while (!_exit)
	{
		_handleEvents();
		_render();
	}
}

void ScoreBoardState::_render()
{
	SDL_RenderClear(_renderer);
	_scoreboard->render();
	_button->render();
	SDL_RenderPresent(_renderer);
}

void ScoreBoardState::_handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !_exit)
	{
		if (event.type == SDL_QUIT)
		{
			_exit = true;
			_game->changeState("gameover");
		}
		else
		{
			_button->handleEvents(event);
		}
	}
}
