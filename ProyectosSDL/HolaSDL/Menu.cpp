#include "Menu.h"

Menu::Menu(Button **buttons, int count)
	: _buttons(buttons), _size(count) {}

void Menu::render() const
{
	for (int i = 0; i < _size; i++)
	{
		_buttons[i]->render();
	}
}

void Menu::handleEvents(SDL_Event event)
{
	for (int i = 0; i < _size; i++)
	{
		_buttons[i]->handleEvents(event);
	}
}
