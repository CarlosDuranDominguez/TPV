#include "MenuState.h"
#include "Button.h"
#include <functional>

MenuState::MenuState(Game* game):  game(game) {
	buttons = new Button* [NUMBER_BUTTONS_MENU];
	SDL_Color white = { 255,255,255,255 };
	SDL_Color grey = { 80,80,80,255 };
	string nombres[NUMBER_BUTTONS_MENU] = { "Play","ScoreBoard","Exit" };
	function<void()> callbacks[NUMBER_BUTTONS_MENU] = {
		[]() {},
		[]() {},
		[]() {}
	};

	for (int i = 0; i < NUMBER_BUTTONS_MENU; i++) {
		buttons[i] = new Button(game->getFonts()[0], 0, i*110, 200, 100, white, grey, nombres[i], callbacks[i]);
	}
	menu = new Menu(buttons, NUMBER_BUTTONS_MENU);
}

MenuState::~MenuState() {
	for (int i = 0; i < NUMBER_BUTTONS_MENU; i++) {
		delete buttons[i];
	}
	delete[] buttons;
	delete menu;
}

void MenuState::run() {
	while (!exit) {
		handleEvents();
		render();
	}
}

void MenuState::render() {
	for (int i = 0; i < NUMBER_BUTTONS_MENU; i++) {
		buttons[i]->render();
	}
}

void MenuState::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT)
			exit = true;
		else{ 
			for (int i = 0; i < NUMBER_BUTTONS_MENU; i++) {
				buttons[i]->handleEvents(event);
			}
		}
	}
}