#pragma once

#include <string>

class Game{};

class LoadManager {
public:
	static void load(Game*, std::string);
	static void save(Game*, std::string);
};