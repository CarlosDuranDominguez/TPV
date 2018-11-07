#include "MenuState.h"
#include "Button.h"
#include "Game.h"
#include <functional>

/**
 * Constructor.
 */
MenuState::MenuState(Game *game, SDL_Renderer *renderer) : _game(game), _renderer(renderer)
{
	_buttons = new Button *[NUMBER_BUTTONS_MENU];
	string nombres[NUMBER_BUTTONS_MENU] = {"Play", "ScoreBoard", "Exit"};
	function<void()> callbacks[NUMBER_BUTTONS_MENU] = {
		[this, game]() { _exit = true; game->changeState("game"); },
		[this, game]() { _exit = true; game->changeState("scoreboard"); },
		[this, game]() { _exit = true; game->changeState("gameover"); }
	};

	for (int i = 0; i < NUMBER_BUTTONS_MENU; i++)
	{
		_buttons[i] = new Button(game->getFonts()[0], 0, i * 110, 200, 100, WHITE, GREY, nombres[i], callbacks[i]);
	}
	_menu = new Menu(_buttons, NUMBER_BUTTONS_MENU);
}

/**
 * Destructor.
 */
MenuState::~MenuState()
{
	for (int i = 0; i < NUMBER_BUTTONS_MENU; i++)
	{
		delete _buttons[i];
	}
	delete[] _buttons;
	delete _menu;
}

/**
 * It executes the main loop of the state.
 */
void MenuState::run()
{
	_exit = false;
	while (!_exit)
	{
		_handleEvents();
		_render();
	}
}

/**
 * It renders every button of the state.
 */
void MenuState::_render()
{
	SDL_RenderClear(_renderer);
	for (int i = 0; i < NUMBER_BUTTONS_MENU; i++)
	{
		_buttons[i]->render();
	}
	SDL_RenderPresent(_renderer);
}

/**
 * It detects user input and change the state.
 */
void MenuState::_handleEvents()
{
	SDL_Event event;
	while (!_exit && SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			_exit = true;
			_game->changeState("gameover");
		}
		else
		{
			for (int i = 0; i < NUMBER_BUTTONS_MENU; i++)
			{
				_buttons[i]->handleEvents(event);
			}
		}
	}
}
