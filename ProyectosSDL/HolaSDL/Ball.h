#pragma once

#include "Vector2D.h"
#include "Texture.h"

class Game;
class Ball {
private:
	Vector2D position;
	int width, heigth;
	Vector2D velocity;
	Texture* texture;
	Game* game;
public:
	Ball();
	Ball(Vector2D position, int width, int heigth, Texture* texture, Game* game);
	Ball(double x, double y, int width, int heigth, Texture* texture, Game* game);
	void render();
	void update();
};

