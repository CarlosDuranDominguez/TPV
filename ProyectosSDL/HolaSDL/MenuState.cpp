#include "MenuState.h"
#include "Button.h"
#include "Game.h"
#include <functional>

/**
 * Constructor.
 */
MenuState::MenuState(Game *game, SDL_Renderer *renderer) :State(game, renderer)
{
	auto _buttons = new Button *[NUMBER_BUTTONS_MENU];
	string nombres[NUMBER_BUTTONS_MENU] = {"Play", "ScoreBoard", "Exit"};
	function<void()> callbacks[NUMBER_BUTTONS_MENU] = {
		[this, game]() { _exit = true; game->changeState(GAME); },
		[this, game]() { _exit = true; game->changeState(SCOREBOARD); },
		[this, game]() { _exit = true; game->changeState(GAMEOVER); }};

	for (int i = 0; i < NUMBER_BUTTONS_MENU; i++)
	{
		_buttons[i] = new Button(game->getFonts()[BIGFONT], 0, i * 110, 200, 100, WHITE, GREY, nombres[i], callbacks[i]);
		add(*_buttons[i]);
	}
	delete[] _buttons;
}

/**
 * Destructor.
 */
MenuState::~MenuState()
{
}
