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
	BlocksMap(string,int, Texture*);
	~BlocksMap();
	void loadMap(string,int, Texture*);
	void render();
	int numberOfBlocks();
	bool collide(const Ball*, Vector2D&, Vector2D&);

};

