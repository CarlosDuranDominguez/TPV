#include "GameState.h"
#include "Ball.h"
#include "Texture.h"
#include "Game.h"

Ball::Ball() : _position(), _width(), _height(), _velocity(), _texture(), _game(nullptr), _radius(((double)_width) / 2) {}

Ball::Ball(Vector2D position, int width, int heigth, Texture *texture, GameState *game)
	: _position(position), _width(width), _height(heigth), _velocity(), _texture(texture), _game(game), _radius(((double)width) / 2) {}

Ball::Ball(double x, double y, int width, int heigth, Texture *texture, GameState *game)
	: _position(x, y), _width(width), _height(heigth), _velocity(), _texture(texture), _game(game), _radius(((double)width) / 2) {}

void Ball::render() const
{
	_texture->render(SDL_Rect {
		(int)_position.getX(),
		(int)_position.getY(),
		_width,
		_height
	});
}

void Ball::update()
{
	_position = _position + _velocity / FRAMERATE;
	Vector2D collision;
	Vector2D auxVelocity = _velocity / FRAMERATE;
	double length = auxVelocity.modulus();
	Vector2D reflection;
	Vector2D centerPosition;
	while (_game->collides(this, collision, reflection))
	{
		auxVelocity = (position() - collision).modulus() / length * auxVelocity.reflect(reflection).normalize();
		setPosition(collision + auxVelocity + reflection.normalize() * _radius);
		_velocity = auxVelocity.normalize() * _velocity.modulus();
	}
}

double Ball::getRadius() const
{
	return _radius;
}

Vector2D Ball::position() const
{
	return Vector2D(_width / 2 + _position.getX(), _height / 2 + _position.getY());
}

Vector2D Ball::setPosition(const double x, const double y)
{
	Vector2D pos(x, y);
	_position = pos - Vector2D(_width / 2, _height / 2);
	return pos;
}

Vector2D Ball::setPosition(const Vector2D pos)
{
	_position = pos - Vector2D(_width / 2, _height / 2);
	return pos;
}

Vector2D Ball::velocity() const
{
	return _velocity;
}

Vector2D Ball::setVelocity(const double x, const double y)
{
	_velocity.setX(x);
	_velocity.setY(y);
	return _velocity;
}
