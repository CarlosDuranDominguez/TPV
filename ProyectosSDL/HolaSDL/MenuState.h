#pragma once

#include "checkML.h"
#include "SDL.h"
#include "Menu.h"
#include "Button.h"

class Game;

const unsigned int NUMBER_BUTTONS_MENU = 3;

class MenuState
{
private:
	Game *_game;
	SDL_Renderer *_renderer;
	Menu *_menu;
	Button **_buttons;
	bool _exit = false;
	void _render();
	void _handleEvents();

public:
	MenuState(Game *game, SDL_Renderer *renderer);
	~MenuState();
	void run();
};
