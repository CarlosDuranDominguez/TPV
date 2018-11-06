#include "Menu.h"

Menu::Menu(Button **buttons, int count)
	: buttons(buttons), size(count) {}

void Menu::render()
{
	for (int i = 0; i < size; i++)
	{
		buttons[i]->render();
	}
}

void Menu::handleEvents(SDL_Event event)
{
	for (int i = 0; i < size; i++)
	{
		buttons[i]->handleEvents(event);
	}
}
