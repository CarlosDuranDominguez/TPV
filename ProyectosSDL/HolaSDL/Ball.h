#pragma once

#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"

class GameState;

class Ball
{
private:
	Vector2D _position;
	int _width, _height;
	double _radius;
	Vector2D _velocity;
	Texture *_texture;
	GameState *_game;

public:
	Ball();
	Ball(Vector2D position, int width, int heigth, Texture *texture, GameState *game);
	Ball(double x, double y, int width, int heigth, Texture *texture, GameState *game);
	void render() const;
	void update();
	double getRadius() const;
	Vector2D position() const;
	Vector2D setPosition(const double x, const double y);
	Vector2D setPosition(const Vector2D pos);
	Vector2D velocity() const;
	Vector2D setVelocity(const double x, const double y);
};
