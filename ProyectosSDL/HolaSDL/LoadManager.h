#pragma once

#include "checkML.h"
#include <string>
#include "Game.h"

using namespace std;

class LoadManager
{
public:
	static void load(Game *game, string filename);
	static void save(Game *game, string filename);
};
