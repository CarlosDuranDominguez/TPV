#include "Ball.h"
#include "Texture.h"
#include <Box2D\Box2D.h>

/**
 * Constructors.
 */
Ball::Ball()
	: _position(), _width(), _height(), _velocity(), _texture(), _radius(((double)_width) / 2) {}

Ball::Ball(Vector2D position, int width, int heigth, Texture *texture)
	: _position(position), _width(width), _height(heigth), _velocity(), _texture(texture), _radius(((double)width) / 2) {}

Ball::Ball(double x, double y, int width, int heigth, Texture *texture)
	: _position(x, y), _width(width), _height(heigth), _velocity(), _texture(texture), _radius(((double)width) / 2) {}

/**
 * Ball's texture is renderized in the correct position.
 */
void Ball::render() const
{
	_texture->render(SDL_Rect{
		(int)_position.getX(),
		(int)_position.getY(),
		_width,
		_height});
}

/**
 * Update the position and detects the collisions.
 */
void Ball::update()
{
}

/**
 * Get the radius of the ball.
 */
double Ball::getRadius() const
{
	return _radius;
}

/**
 * Get the center's position.
 */
Vector2D Ball::position() const
{
	return Vector2D(_width / 2 + _position.getX(), _height / 2 + _position.getY());
}

/**
 * Set the center's position.
 */
Vector2D Ball::setPosition(const double x, const double y)
{
	Vector2D pos(x, y);
	_position = pos - Vector2D(_width / 2, _height / 2);
	return pos;
}

/**
 * Set the center's position.
 */
Vector2D Ball::setPosition(const Vector2D pos)
{
	_position = pos - Vector2D(_width / 2, _height / 2);
	return pos;
}

/**
 * Get the vector of the velocity.
 */
Vector2D Ball::velocity() const
{
	return _velocity;
}

/**
 * Set the vector of the velocity.
 */
Vector2D Ball::setVelocity(const double x, const double y)
{
	_velocity.setX(x);
	_velocity.setY(y);
	return _velocity;
}
