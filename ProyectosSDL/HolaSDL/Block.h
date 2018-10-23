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
	Block();
	Block(float x, float y, int width, int height, int column, int row, int color, Texture* texture);
	Block(Vector2D position, int width, int height, int column, int row, int color, Texture* texture);
	~Block();
	void render();
};


