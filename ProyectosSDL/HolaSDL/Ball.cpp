#include "Game.h"
#include"Ball.h"
#include "Texture.h"

Ball::Ball() :
	position(), width(), heigth(), velocity(), texture(), game(nullptr),radius(((double)width)/2) {};
Ball::Ball(Vector2D position, int width, int heigth, Texture* texture, Game* game):
	position(position), width(width), heigth(heigth), velocity(), texture(texture), game(game) {};
Ball::Ball(double x, double y, int width, int heigth, Texture* texture, Game* game) :
	position(x, y), width(width), heigth(heigth), velocity(), texture(texture), game(game) {};
void Ball::render()
{
	texture->render(SDL_Rect{(int)position.getX(),(int)position.getY(),width,heigth});
};
void Ball::update() {
	position = position + velocity / FRAMERATE;
	Vector2D collision;
	Vector2D auxVelocity = velocity;
	if (game->collides(this, collision, auxVelocity)) {

	}
};

double Ball::getRadius() const {
	return radius;
}
Vector2D Ball::Position() const {
	return Vector2D(width / 2 + position.getX(), heigth / 2 + position.getY());
}