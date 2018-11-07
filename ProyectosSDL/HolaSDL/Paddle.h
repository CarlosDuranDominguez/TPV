#pragma once

#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"
#include "Ball.h"

class Game;

class Paddle
{
private:
	Game *_game;
	Vector2D _position;
	int _width, _height;
	Vector2D _velocity;
	double _speed;
	Texture *_texture;
	bool _leftMovement, _rightMovement;

public:
	Paddle(Game *game, Vector2D position, int width, int heigth, double speed, Texture *texture);
	Paddle(Game *game, double x, double y, int width, int heigth, double speed, Texture *texture);
	void render() const;
	void update();
	void handleEvents(SDL_Event event);
	bool collide(const Ball *, Vector2D &, Vector2D &);
	Vector2D position() const;
	Vector2D setPosition(const double x, const double y);
	Vector2D setPosition(const Vector2D pos);
	Vector2D velocity() const;
	Vector2D setVelocity(const double x, const double y);
};
