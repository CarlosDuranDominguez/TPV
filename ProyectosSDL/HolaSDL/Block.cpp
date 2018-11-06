#include "Block.h"
#include "Ball.h"
#include "Texture.h"

Block::Block() : position(), width(), height(), column(), row(), color(), texture() {}

Block::Block(float x, float y, int width, int height, int column, int row, int color, Texture *texture)
	: position(x, y), width(width), height(height), column(column), row(row), color(color), texture(texture) {}

Block::Block(Vector2D position, int width, int height, int column, int row, int color, Texture *texture)
	: position(position), width(width), height(height), column(column), row(row), color(color), texture(texture) {}

Block::~Block() {}

void Block::render()
{
	texture->renderFrame(
		SDL_Rect {
			(int)position.getX(),
			(int)position.getY(),
			width,
			height
		},
		color / texture->getNumCols(),
		color % texture->getNumCols()
	);
}

bool Block::collide(const Ball *object, Vector2D &collisionPosition, Vector2D &reflection)
{
	if (object->position().isIn(position.getX() - object->getRadius(),
			position.getY(),
			position.getX() + width + object->getRadius(),
			position.getY() + height) ||
		object->position().isIn(position.getX(),
			position.getY() - object->getRadius(),
			position.getX() + width,
			position.getY() + height + object->getRadius()) ||
		(object->position() - Vector2D(position.getX() + width, position.getY() + height)).modulus() < object->getRadius() ||
		(object->position() - Vector2D(position.getX(), position.getY() + height)).modulus() < object->getRadius() ||
		(object->position() - Vector2D(position.getX() + width, position.getY())).modulus() < object->getRadius() ||
		(object->position() - Vector2D(position.getX(), position.getY())).modulus() < object->getRadius())
	{
		if ((object->position().getY() - position.getY()) * (width) -
				(object->position().getX() - position.getX()) * (height) <
			0.0)
		{
			if ((object->position().getY() - position.getY() - height) * (width) -
					(object->position().getX() - position.getX()) * (-height) <
				0.0)
			{
				reflection = Vector2D(0, -1);
				collisionPosition = Vector2D::cutPoint(
					object->position() + Vector2D(0, object->getRadius()),
					object->position() + Vector2D(0, object->getRadius()) + object->velocity(),
					position + Vector2D(0, 0), position + Vector2D(width, 0)
				);
			}
			else
			{
				reflection = Vector2D(1, 0);
				collisionPosition = Vector2D::cutPoint(
					object->position() - Vector2D(object->getRadius(), 0),
					object->position() - Vector2D(object->getRadius(), 0) + object->velocity(),
					position + Vector2D(width, 0), position + Vector2D(width, height)
				);
			}
		}
		else
		{
			if ((object->position().getY() - position.getY() - height) * (width) -
					(object->position().getX() - position.getX()) * (-height) <
				0.0)
			{
				reflection = Vector2D(-1, 0);
				collisionPosition = Vector2D::cutPoint(
					object->position() + Vector2D(object->getRadius(), 0),
					object->position() + Vector2D(object->getRadius(), 0) + object->velocity(),
					position + Vector2D(0, 0), position + Vector2D(0, height)
				);
			}
			else
			{
				reflection = Vector2D(0, 1);
				collisionPosition = Vector2D::cutPoint(
					object->position() - Vector2D(0, object->getRadius()),
					object->position() - Vector2D(0, object->getRadius()) + object->velocity(),
					position + Vector2D(0, height), position + Vector2D(width, height)
				);
			}
		}

		return true;
	}

	return false;
}
