#pragma once

#include "Vector2D.h"
#include "Texture.h"

class Game;
class Ball {
private:
	Vector2D position;
	int width, height;
	double radius;
	Vector2D velocity;
	Texture* texture;
	Game* game;
public:
	Ball();
	Ball(Vector2D position, int width, int heigth, Texture* texture, Game* game);
	Ball(double x, double y, int width, int heigth, Texture* texture, Game* game);
	void render();
	void update();
	double getRadius() const;
	Vector2D Position() const;
	Vector2D SetPosition(const double x, const double y);
	Vector2D SetPosition(Vector2D pos);
	Vector2D Velocity() const;
	Vector2D setVelocity(const double x, const double y);
};

