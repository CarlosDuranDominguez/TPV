#include "Paddle.h"
#include "Game.h"
#include "SDL.h"

Paddle::Paddle(Vector2D position, int width, int heigth, double speed, Texture* texture) :
	position(position), width(width), heigth(heigth), velocity(), speed(), texture(texture), 
	leftMovement(false), rightMovement(false) {};
Paddle::Paddle(double x, double y, int width, int heigth, double speed, Texture* texture) :
	position(x, y), width(width), heigth(heigth), velocity(), speed(speed), texture(texture),
	leftMovement(false), rightMovement(false) {};
void Paddle::render() const
{
	texture->render(SDL_Rect{ (int)position.getX(),(int)position.getY(),width,heigth });
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
	return Vector2D(width / 2 + position.getX(), heigth / 2 + position.getY());
}
bool Paddle::collide(const Ball* object, Vector2D& collisionPosition, Vector2D& reflection) {
	if (object->Position().isIn(position.getX() - width - object->getRadius(),
			position.getY() - heigth,
			position.getX() + width + object->getRadius(),
			position.getY() + heigth) ||
		object->Position().isIn(position.getX() - width ,
			position.getY() - heigth - object->getRadius(),
			position.getX() + width,
			position.getY() + heigth + object->getRadius()) ||
		(object->Position() - Vector2D(position.getX() + width, position.getY() + heigth)).modulus<object->getRadius() ||
		(object->Position() - Vector2D(position.getX(), position.getY() + heigth)).modulus < object->getRadius() ||
		(object->Position() - Vector2D(position.getX() + width, position.getY())).modulus < object->getRadius() ||
		(object->Position() - Vector2D(position.getX(), position.getY())).modulus < object->getRadius() ) {
		if (noseque > 0.0) {
			if (nosecual > 0.0) {
				reflection = Vector2D(?, ?);
				collisionPosition = corte;
			}
			else {
				reflection = Vector2D(?, ?);
				collisionPosition = corte;
			}
		}
		else {
			if (nosecual > 0.0) {
				reflection = Vector2D(?, ?);
				collisionPosition = corte;
			}
			else {
				reflection = Vector2D(?, ?);
				collisionPosition = corte;
			}
		}
		return true;
	}
	return false;
}