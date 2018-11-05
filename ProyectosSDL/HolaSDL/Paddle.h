#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include "Ball.h"
class Paddle {
private:
	Vector2D position;
	int width, height;
	Vector2D velocity;
	double speed;
	Texture* texture;
	bool leftMovement, rightMovement;
public:
	Paddle(Vector2D position, int width, int heigth, double speed ,Texture* texture);
	Paddle(double x, double y, int width, int heigth, double speed, Texture* texture);
	void render() const;
	void update();
	void handleEvents(SDL_Event event);
	bool collide(const Ball*, Vector2D&, Vector2D&);
	Vector2D Position() const;
};

