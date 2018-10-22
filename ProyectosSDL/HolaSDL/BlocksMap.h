#pragma once

#include "Block.h"
#include <string>
class BlocksMap {
private:
	Block** blocks;
	int columns, rows;
	int mapWidth, mapHeight;
	int cellWidth, cellHeight;
public:
	BlocksMap() :
		blocks(nullptr), columns(0), rows(0), mapWidth(0), mapHeight(0), cellWidth(0), cellHeight(0) {};
	BlocksMap(string path) { loadMap(path); };
	~BlocksMap();
	void loadMap(string);
	void render();
	int numberOfBlocks();
	Block* collide();

};

