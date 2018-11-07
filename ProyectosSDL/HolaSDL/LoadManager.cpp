#include "LoadManager.h"
#include <fstream>

/**
 * Load a level save file
 */
void LoadManager::load(Game *game, string filename)
{
	// Open a readonly file stream
	fstream file;
	file.open(filename, fstream::in);

	// Read the level
	int level;
	file >> level;

	// Set the level to the game manager
	game->gameManager()->setLevel(level);

	// Close the file stream
	file.close();
}

/**
 * Save a level save file
 */
void LoadManager::save(Game *game, string filename)
{
	// Open a writeonly file stream
	fstream file;
	file.open(filename, fstream::out);

	// Write down the level
	int level = game->gameManager()->level();
	file << level;

	// Close the file stream
	file.close();
}
