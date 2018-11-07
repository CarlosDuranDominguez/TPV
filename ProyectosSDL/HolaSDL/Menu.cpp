#include "Menu.h"

/*
 * Constructor.
 */
Menu::Menu(Button **buttons, int count)
	: _buttons(buttons), _size(count) {}

/*
 * It renders every button.
 */
void Menu::render() const
{
	for (int i = 0; i < _size; i++)
	{
		_buttons[i]->render();
	}
}

/*
 * It detects all interactions with every button.
 */
void Menu::handleEvents(SDL_Event event)
{
	for (int i = 0; i < _size; i++)
	{
		_buttons[i]->handleEvents(event);
	}
}
