#include "MenuState.h"
#include "Button.h"
#include "Game.h"
#include <functional>

MenuState::MenuState(Game *game, SDL_Renderer *renderer) : game(game), renderer(renderer)
{
	buttons = new Button *[NUMBER_BUTTONS_MENU];
	string nombres[NUMBER_BUTTONS_MENU] = {"Play", "ScoreBoard", "Exit"};
	function<void()> callbacks[NUMBER_BUTTONS_MENU] = {
		[this, game]() { exit = true; game->changeState("game"); },
		[this, game]() { exit = true; game->changeState("scoreboard"); },
		[this, game]() { exit = true; game->changeState("gameover"); }
	};

	for (int i = 0; i < NUMBER_BUTTONS_MENU; i++)
	{
		buttons[i] = new Button(game->getFonts()[0], 0, i * 110, 200, 100, WHITE, GREY, nombres[i], callbacks[i]);
	}
	menu = new Menu(buttons, NUMBER_BUTTONS_MENU);
}

MenuState::~MenuState()
{
	for (int i = 0; i < NUMBER_BUTTONS_MENU; i++)
	{
		delete buttons[i];
	}
	delete[] buttons;
	delete menu;
}

void MenuState::run()
{
	exit = false;
	while (!exit)
	{
		handleEvents();
		render();
	}
}

void MenuState::render()
{
	SDL_RenderClear(renderer);
	for (int i = 0; i < NUMBER_BUTTONS_MENU; i++)
	{
		buttons[i]->render();
	}
	SDL_RenderPresent(renderer);
}

void MenuState::handleEvents()
{
	SDL_Event event;
	while (!exit && SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			exit = true;
			game->changeState("gameover");
		}
		else
		{
			for (int i = 0; i < NUMBER_BUTTONS_MENU; i++)
			{
				buttons[i]->handleEvents(event);
			}
		}
	}
}
