#pragma once

#include "checkML.h"
#include "Block.h"
#include <string>
#include "Vector2D.h"

class BlocksMap
{
  private:
	Block ***_blocks;
	uint _numberOfBlocks;
	Vector2D _position;
	int _columns, _rows;
	int _mapWidth, _mapHeight;
	int _cellWidth, _cellHeight;
	void _freeBlocks();

  public:
	BlocksMap(Vector2D position, int width, int height);
	BlocksMap(double x, double y, int width, int height);
	BlocksMap(Vector2D position, int width, int height, string path, Texture *texture);
	BlocksMap(double x, double y, int width, int height, string path, Texture *texture);
	~BlocksMap();
	void loadMap(string path, Texture *texture);
	void saveMap(string path) const;
	void render() const;
	int numberOfBlocks() const;
	bool collide(const Ball *, Vector2D &, Vector2D &);
};
