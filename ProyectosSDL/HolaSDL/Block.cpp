#include "Block.h"
#include "Ball.h"
#include "Texture.h"

/**
 * Constructors.
 */
Block::Block() : _position(), _width(), _height(), _column(), _row(), _color(), _texture() {}

Block::Block(float x, float y, int width, int height, int column, int row, int color, Texture *texture)
	: _position(x, y), _width(width), _height(height), _column(column), _row(row), _color(color), _texture(texture) {}

Block::Block(Vector2D position, int width, int height, int column, int row, int color, Texture *texture)
	: _position(position), _width(width), _height(height), _column(column), _row(row), _color(color), _texture(texture) {}

/**
 * Destructor.
 */
Block::~Block() {}

/**
 * Block's texture is renderized in the correct position.
 */
void Block::render() const
{
	_texture->renderFrame(
		SDL_Rect{
			(int)_position.getX(),
			(int)_position.getY(),
			_width,
			_height},
		_color / _texture->getNumCols(),
		_color % _texture->getNumCols());
}

/**
 * Detects if the circular object collides with the block and return the position
 * of the collision and the reflection vector(normal vector of the side).
 */
bool Block::collide(const Ball *object, Vector2D &collisionPosition, Vector2D &reflection)
{
	if (object->position().isIn(_position.getX() - object->getRadius(),
								_position.getY(),
								_position.getX() + _width + object->getRadius(),
								_position.getY() + _height) ||
		object->position().isIn(_position.getX(),
								_position.getY() - object->getRadius(),
								_position.getX() + _width,
								_position.getY() + _height + object->getRadius()) ||
		(object->position() - Vector2D(_position.getX() + _width, _position.getY() + _height)).modulus() < object->getRadius() ||
		(object->position() - Vector2D(_position.getX(), _position.getY() + _height)).modulus() < object->getRadius() ||
		(object->position() - Vector2D(_position.getX() + _width, _position.getY())).modulus() < object->getRadius() ||
		(object->position() - Vector2D(_position.getX(), _position.getY())).modulus() < object->getRadius())
	{
		if ((object->position().getY() - _position.getY()) * (_width) -
				(object->position().getX() - _position.getX()) * (_height) <
			0.0)
		{
			if ((object->position().getY() - _position.getY() - _height) * (_width) -
					(object->position().getX() - _position.getX()) * (-_height) <
				0.0)
			{
				reflection = Vector2D(0, -1);
				collisionPosition = Vector2D::cutPoint(
					object->position() + Vector2D(0, object->getRadius()),
					object->position() + Vector2D(0, object->getRadius()) + object->velocity(),
					_position + Vector2D(0, 0), _position + Vector2D(_width, 0));
			}
			else
			{
				reflection = Vector2D(1, 0);
				collisionPosition = Vector2D::cutPoint(
					object->position() - Vector2D(object->getRadius(), 0),
					object->position() - Vector2D(object->getRadius(), 0) + object->velocity(),
					_position + Vector2D(_width, 0), _position + Vector2D(_width, _height));
			}
		}
		else
		{
			if ((object->position().getY() - _position.getY() - _height) * (_width) -
					(object->position().getX() - _position.getX()) * (-_height) <
				0.0)
			{
				reflection = Vector2D(-1, 0);
				collisionPosition = Vector2D::cutPoint(
					object->position() + Vector2D(object->getRadius(), 0),
					object->position() + Vector2D(object->getRadius(), 0) + object->velocity(),
					_position + Vector2D(0, 0), _position + Vector2D(0, _height));
			}
			else
			{
				reflection = Vector2D(0, 1);
				collisionPosition = Vector2D::cutPoint(
					object->position() - Vector2D(0, object->getRadius()),
					object->position() - Vector2D(0, object->getRadius()) + object->velocity(),
					_position + Vector2D(0, _height), _position + Vector2D(_width, _height));
			}
		}

		return true;
	}

	return false;
}

/**
 * Returns the colour.
 */
int Block::getColor() const
{
	return _color;
}
