#include "ScoreBoardState.h"
#include "Game.h"

/**
 * Constructor.
 */
ScoreBoardState::ScoreBoardState(Game *game, SDL_Renderer *renderer) : _game(game), _renderer(renderer)
{
	_scoreboard = new ScoreBoard(game->getFonts()[MEDIUMFONT], 0, 0, 200, 40, WHITE, "../saves/save.save");
	_button = new Button(game->getFonts()[0], 0, 400, 200, 100, WHITE, GREY, "Exit", [this, game]() {
		_exit = true;
		game->changeState(MENU);
	});
}

/**
 * Destructor.
 */
ScoreBoardState::~ScoreBoardState()
{
	delete _scoreboard;
	delete _button;
}

/**
 * It executes the loop of the state.
 */
void ScoreBoardState::run()
{
	_exit = false;
	while (!_exit)
	{
		_handleEvents();
		_render();
	}
}

/**
 * It renders the button and the scoreboard.
 */
void ScoreBoardState::_render()
{
	SDL_RenderClear(_renderer);
	_scoreboard->render();
	_button->render();
	SDL_RenderPresent(_renderer);
}

/**
 * It detects the user's input.
 */
void ScoreBoardState::_handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !_exit)
	{
		if (event.type == SDL_QUIT)
		{
			_exit = true;
			_game->changeState(GAMEOVER);
		}
		else
		{
			_button->handleEvents(event);
		}
	}
}

/**
 * It put a new game in the record.
 */
void ScoreBoardState::pushNewFinishGame(const string &name, int score, int time)
{
	_scoreboard->pushGame({name, score, time});
}
