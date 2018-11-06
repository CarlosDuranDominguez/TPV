#pragma once

#include "Button.h"

class Menu {
private:
	Button* buttons;
public:
	Menu(Button*...);
	void render();
	void handleEvents();
};