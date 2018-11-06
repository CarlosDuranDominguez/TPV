#include "Wall.h"

Wall::Wall(float x, float y, int width, int height, Texture* texture)
	:position(x, y), width(width), height(height), texture(texture) {};

Wall::Wall(Vector2D position, int width, int height, Texture* texture)
	: position(position), width(width), height(height), texture(texture) {};

Wall::~Wall() {};

void Wall::render() {
	texture->render(SDL_Rect{ (int)position.getX(),(int)position.getY(),width,height });
};

bool Wall::collide(const Ball* object, Vector2D& collisionPosition, Vector2D& reflection) {
	if (object->Position().isIn(position.getX() - object->getRadius(),
		position.getY(),
		position.getX() + width + object->getRadius(),
		position.getY() + height) ||
		object->Position().isIn(position.getX(),
			position.getY() - object->getRadius(),
			position.getX() + width,
			position.getY() + height + object->getRadius()) ||
			(object->Position() - Vector2D(position.getX() + width, position.getY() + height)).modulus() < object->getRadius() ||
		(object->Position() - Vector2D(position.getX(), position.getY() + height)).modulus() < object->getRadius() ||
		(object->Position() - Vector2D(position.getX() + width, position.getY())).modulus() < object->getRadius() ||
		(object->Position() - Vector2D(position.getX(), position.getY())).modulus() < object->getRadius()) {
		if ((object->Position().getY() - position.getY()) * (width)-
			(object->Position().getX() - position.getX()) * (height) < 0.0) {
			if ((object->Position().getY() - position.getY() - height) * (width)-
				(object->Position().getX() - position.getX()) * (-height) < 0.0) {
				reflection = Vector2D(0, -1);
				collisionPosition = Vector2D::cutPoint(object->Position() + Vector2D(0, object->getRadius()), object->Position() + Vector2D(0, object->getRadius()) + object->Velocity(),
					position + Vector2D(0, 0), position + Vector2D(width, 0));
			}
			else {
				reflection = Vector2D(1, 0);
				collisionPosition = Vector2D::cutPoint(object->Position() - Vector2D(object->getRadius(), 0), object->Position() - Vector2D(object->getRadius(), 0) + object->Velocity(),
					position + Vector2D(width, 0), position + Vector2D(width, height));
			}
		}
		else {
			if ((object->Position().getY() - position.getY() - height) * (width)-
				(object->Position().getX() - position.getX()) * (-height) < 0.0) {
				reflection = Vector2D(-1, 0);
				collisionPosition = Vector2D::cutPoint(object->Position() + Vector2D(object->getRadius(), 0), object->Position() + Vector2D(object->getRadius(), 0) + object->Velocity(),
					position + Vector2D(0, 0), position + Vector2D(0, height));
			}
			else {
				reflection = Vector2D(0, 1);
				collisionPosition = Vector2D::cutPoint(object->Position() - Vector2D(0, object->getRadius()), object->Position() - Vector2D(0, object->getRadius()) + object->Velocity(),
					position + Vector2D(0, height), position + Vector2D(width, height));
			}
		}
		return true;
	}
	return false;
}