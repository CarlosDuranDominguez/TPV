#pragma once

#include "Vector2D.h"
#include "Texture.h"

class Paddle {
private:
	Vector2D position;
	int width, heigth;
	Vector2D velocity;
	double speed;
	Texture* texture;
public:
	Paddle(Vector2D position, int width, int heigth, double speed ,Texture* texture);
	Paddle(double x, double y, int width, int heigth, double speed, Texture* texture);
	void render();
	void update();
	void handleEvents(SDL_Event event);
	Vector2D colision();
};

