#pragma once

#include "Vector2D.h"
#include "Texture.h"

class Wall {
private:
	Vector2D position;
	int width, height;
	Texture* texture;
public:
	Wall(float x, float y, int width, int height, Texture* texture);
	Wall(Vector2D position, int width, int height, Texture* texture);
	~Wall();
	void render();
};

