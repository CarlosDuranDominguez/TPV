#pragma once

#include "Block.h"
#include <string>

class BlocksMap
{
private:
	Block ***_blocks;
	uint _numberOfBlocks;
	int _columns, _rows;
	int _mapWidth, _mapHeight;
	int _cellWidth, _cellHeight;

public:
	BlocksMap(int padding);
	BlocksMap(string, int, Texture *);
	~BlocksMap();
	void loadMap(string, int, Texture *);
	void render() const;
	int numberOfBlocks() const;
	bool collide(const Ball *, Vector2D &, Vector2D &);
};
