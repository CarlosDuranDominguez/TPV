#pragma once

#include "Button.h"

class Menu {
private:
	Button** buttons;
	int size;
public:
	Menu(Button**, int);
	void render();
	void handleEvents(SDL_Event event);
};