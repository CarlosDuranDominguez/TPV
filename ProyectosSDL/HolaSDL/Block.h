#pragma once

#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"

class Ball;

class Block
{
private:
	Vector2D _position;
	int _width, _height;
	int _column, _row;
	int _color;
	Texture *_texture;

public:
	Block();
	Block(float x, float y, int width, int height, int column, int row, int color, Texture *texture);
	Block(Vector2D position, int width, int height, int column, int row, int color, Texture *texture);
	~Block();
	void render() const;
	bool collide(const Ball *, Vector2D &, Vector2D &);
	int getColor() const;
};
