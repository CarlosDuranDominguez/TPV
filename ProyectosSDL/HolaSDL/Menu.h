#pragma once

#include "checkML.h"
#include "Button.h"

class Menu
{
private:
	Button **_buttons;
	int _size;

public:
	Menu(Button **, int);
	void render() const;
	void handleEvents(SDL_Event event);
};
