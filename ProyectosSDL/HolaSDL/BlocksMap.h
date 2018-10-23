#pragma once

#include "Block.h"
#include <string>
class BlocksMap {
private:
	Block*** blocks;
	int columns, rows;
	int mapWidth, mapHeight;
	int cellWidth, cellHeight;
public:
	BlocksMap(string, Texture*);
	~BlocksMap();
	void loadMap(string, Texture*);
	void render();
	int numberOfBlocks();
	Block* collide();

};

