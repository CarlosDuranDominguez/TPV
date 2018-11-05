#include "Paddle.h"
#include "Game.h"
#include "SDL.h"

Paddle::Paddle(Vector2D position, int width, int heigth, double speed, Texture* texture) :
	position(position), width(width), height(heigth), velocity(), speed(), texture(texture), 
	leftMovement(false), rightMovement(false) {};
Paddle::Paddle(double x, double y, int width, int heigth, double speed, Texture* texture) :
	position(x, y), width(width), height(heigth), velocity(), speed(speed), texture(texture),
	leftMovement(false), rightMovement(false) {};
void Paddle::render() const
{
	texture->render(SDL_Rect{ (int)position.getX(),(int)position.getY(),width,height });
};
void Paddle::update() 
{
	position = position + velocity*FRAMERATE;
};
void Paddle::handleEvents(SDL_Event event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			rightMovement = true;
		break;
		case SDLK_LEFT:
			leftMovement = true;
		break;
		}
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
			rightMovement = false;
			break;
		case SDLK_LEFT:
			leftMovement = false;
			break;
		}
	}
	velocity = Vector2D(0, 0);
	velocity = velocity + (rightMovement ? Vector2D(1, 0) : Vector2D(0, 0));
	velocity = velocity + (leftMovement ? Vector2D(-1, 0) : Vector2D(0, 0));
}
Vector2D Paddle::Position() const {
	return Vector2D(((double)width) / 2 + position.getX(),((double) height) / 2 + position.getY());
}
bool Paddle::collide(const Ball* object, Vector2D& collisionPosition, Vector2D& reflection) {
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
				collisionPosition = Vector2D::cutPoint(object->Position() + Vector2D(0, object->getRadius()), object->Position() + Vector2D(0, object->getRadius()) + object->Velocity(),
					position + Vector2D(0, 0), position + Vector2D(width, 0));
				reflection = Vector2D((object->Position().getX()- Position().getX())/width,-1);
				reflection.normalize();
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

