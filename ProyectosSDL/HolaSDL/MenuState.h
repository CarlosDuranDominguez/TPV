#pragma once
#include "SDL.h"
#include "Menu.h"
#include "Button.h"

class Game;

const unsigned int NUMBER_BUTTONS_MENU = 3;

class MenuState {
private:
	Game* game;
	Menu* menu;
	Button** buttons;
	bool exit = false;
	void render();
	void handleEvents();
public:
	MenuState(Game* game);
	~MenuState();
	void run();
};