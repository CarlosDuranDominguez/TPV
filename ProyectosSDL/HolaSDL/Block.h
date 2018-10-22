#pragma once

#include "Vector2D.h"
#include "Texture.h"
class Block {
private:
	Vector2D position;
	int width, height;
	int column, row;
	int color;
	Texture* texture;
public:
	Block(float x, float y, int width, int height, int column, int row, int color, Texture* texture)
		:position(x, y), width(width), height(height), column(column), row(row), color(color), texture(texture) {};
	Block(Vector2D position, int width, int height, int column, int row, int color, Texture* texture)
		:position(position), width(width), height(height), column(column), row(row), color(color), texture(texture) {};
	~Block() {};
	void render();
};


