#pragma once

#include "Vector2D.h"
#include "Texture.h"

class Paddle {
private:
	Vector2D position;
	int width, heigth;
	Vector2D velocity;
	Texture* texture;
public:
	Paddle(Vector2D position, int width, int heigth, Texture* texture) :
		position(position), width(width), heigth(heigth), velocity(), texture(texture) {};
	Paddle(double x, double y, int width, int heigth, Texture* texture) :
		position(x, y), width(width), heigth(heigth), velocity(), texture(texture) {};
	void render();
	void update();
	void handleEvents(SDL_Event event);
	Vector2D colision();
};

