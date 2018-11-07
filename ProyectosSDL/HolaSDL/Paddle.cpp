#include "Paddle.h"
#include "Game.h"
#include "SDL.h"

/**
 * Constructors.
 */
Paddle::Paddle(Game *game, Vector2D position, int width, int heigth, double speed, Texture *texture)
	: _game(game), _position(position), _width(width), _height(heigth), _velocity(), _speed(), _texture(texture),
	  _leftMovement(false), _rightMovement(false) {};

Paddle::Paddle(Game *game, double x, double y, int width, int heigth, double speed, Texture *texture)
	: _game(game), _position(x, y), _width(width), _height(heigth), _velocity(), _speed(speed), _texture(texture),
	  _leftMovement(false), _rightMovement(false) {};

/**
 * It renders the paddle in the correct position.
 */
void Paddle::render() const
{
	_texture->render(SDL_Rect {
		(int)_position.getX(),
		(int)_position.getY(),
		_width,
		_height
	});
};

/**
 * Update the position of the paddle.
 */
void Paddle::update()
{
	if (_velocity.getX() != 0) {
		_position = _position + _velocity * FRAMERATE;

		int wall_width = _game->getTextures()[TOPSIDE]->getH() * WIN_WIDTH / _game->getTextures()[TOPSIDE]->getW();
		double x = _position.getX();
		if (x < wall_width)
			_position = Vector2D(wall_width, _position.getY());
		else if (x > WIN_WIDTH - wall_width - _width)
			_position = Vector2D(WIN_WIDTH - wall_width - _width, _position.getY());
	}
};

/**
 * It moves the paddle acording with the user's input.
 */
void Paddle::handleEvents(SDL_Event event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			_rightMovement = true;
			break;
		case SDLK_LEFT:
			_leftMovement = true;
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			_rightMovement = false;
			break;
		case SDLK_LEFT:
			_leftMovement = false;
			break;
		}
	}
	double x = (_rightMovement ? 1 : 0) + (_leftMovement ? -1 : 0);
	double y = 0;
	_velocity = Vector2D(x, y);
}

/**
 * Get the center's position.
 */
Vector2D Paddle::position() const
{
	double x = ((double)_width) / 2 + _position.getX();
	double y = ((double)_height) / 2 + _position.getY();
	return Vector2D(x, y);
}

/**
 * Set the center's position.
 */
Vector2D Paddle::setPosition(const double x, const double y)
{
	Vector2D pos(x, y);
	return setPosition(pos);
}

/**
 * Set the center's position.
 */
Vector2D Paddle::setPosition(const Vector2D pos)
{
	_position = pos - Vector2D(_width / 2, _height / 2);
	return pos;
}

/**
 * Get the vector of the velocity.
 */
Vector2D Paddle::velocity() const
{
	return _velocity;
}

/**
 * Set the vector of the velocity.
 */
Vector2D Paddle::setVelocity(const double x, const double y)
{
	_velocity.setX(x);
	_velocity.setY(y);
	return _velocity;
}

/**
 * Detects if the circular object collides with the paddle and return the position of the collision and the reflection vector(normal vector of the side).
 * If the collision happends int the top the reflection vector depends on the distance between the centers.
 */
bool Paddle::collide(const Ball *object, Vector2D &collisionPosition, Vector2D &reflection)
{
	if (object->position().isIn(
			_position.getX() - object->getRadius(),
			_position.getY(),
			_position.getX() + _width + object->getRadius(),
			_position.getY() + _height
		) ||
		object->position().isIn(
			_position.getX(),
			_position.getY() - object->getRadius(),
			_position.getX() + _width,
			_position.getY() + _height + object->getRadius()
		) ||
		(object->position() - Vector2D(_position.getX() + _width, _position.getY() + _height)).modulus() < object->getRadius() ||
		(object->position() - Vector2D(_position.getX(), _position.getY() + _height)).modulus() < object->getRadius() ||
		(object->position() - Vector2D(_position.getX() + _width, _position.getY())).modulus() < object->getRadius() ||
		(object->position() - Vector2D(_position.getX(), _position.getY())).modulus() < object->getRadius())
	{
		if ((object->position().getY() - _position.getY()) * (_width) - (object->position().getX() - _position.getX()) * (_height) < 0.0)
		{
			if ((object->position().getY() - _position.getY() - _height) * (_width) - (object->position().getX() - _position.getX()) * (-_height) < 0.0)
			{
				collisionPosition = Vector2D::cutPoint(
					object->position() + Vector2D(0, object->getRadius()),
					object->position() + Vector2D(0, object->getRadius()) + object->velocity(),
					_position + Vector2D(0, 0), _position + Vector2D(_width, 0)
				);
				reflection = Vector2D((object->position().getX() - position().getX()) / _width, -1);
				reflection.normalize();
			}
			else
			{
				reflection = Vector2D(1, 0);
				collisionPosition = Vector2D::cutPoint(
					object->position() - Vector2D(object->getRadius(), 0),
					object->position() - Vector2D(object->getRadius(), 0) + object->velocity(),
					_position + Vector2D(_width, 0), _position + Vector2D(_width, _height)
				);
			}
		}
		else
		{
			if ((object->position().getY() - _position.getY() - _height) * (_width) - (object->position().getX() - _position.getX()) * (-_height) < 0.0)
			{
				reflection = Vector2D(-1, 0);
				collisionPosition = Vector2D::cutPoint(
					object->position() + Vector2D(object->getRadius(), 0),
					object->position() + Vector2D(object->getRadius(), 0) + object->velocity(),
					_position + Vector2D(0, 0), _position + Vector2D(0, _height)
				);
			}
			else
			{
				reflection = Vector2D(0, 1);
				collisionPosition = Vector2D::cutPoint(
					object->position() - Vector2D(0, object->getRadius()),
					object->position() - Vector2D(0, object->getRadius()) + object->velocity(),
					_position + Vector2D(0, _height), _position + Vector2D(_width, _height)
				);
			}
		}

		return true;
	}

	return false;
}
