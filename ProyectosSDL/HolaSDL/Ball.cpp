#include "GameState.h"
#include"Ball.h"
#include "Texture.h"
#include "Game.h"

Ball::Ball() :
	position(), width(), height(), velocity(), texture(), game(nullptr),radius(((double)width)/2) {};
Ball::Ball(Vector2D position, int width, int heigth, Texture* texture, GameState* game):
	position(position), width(width), height(heigth), velocity(), texture(texture), game(game), radius(((double)width) / 2) {};
Ball::Ball(double x, double y, int width, int heigth, Texture* texture, GameState* game) :
	position(x, y), width(width), height(heigth), velocity(), texture(texture), game(game), radius(((double)width) / 2) {};
void Ball::render()
{
	texture->render(SDL_Rect{(int)position.getX(),(int)position.getY(),width,height});
};
void Ball::update() {
	position = position + velocity / FRAMERATE;
	Vector2D collision;
	Vector2D auxVelocity = velocity / FRAMERATE;
	double length = auxVelocity.modulus();
	Vector2D reflection;
	Vector2D centerPosition;
	while (game->collides(this, collision, reflection)) {
		auxVelocity = (Position() - collision).modulus()/length*auxVelocity.reflect(reflection).normalize();
		SetPosition(collision + auxVelocity+reflection.normalize()*radius);
		velocity = auxVelocity.normalize()*velocity.modulus();
	}
};

double Ball::getRadius() const {
	return radius;
}
Vector2D Ball::Position() const {
	return Vector2D(width / 2 + position.getX(), height / 2 + position.getY());
}
Vector2D Ball::SetPosition(const double x, const double y) {
	Vector2D pos(x, y);
	position = pos - Vector2D(width / 2, height / 2);
	return pos;
}
Vector2D Ball::SetPosition(Vector2D pos) {
	position = pos - Vector2D(width / 2, height / 2);
	return pos;
}
Vector2D Ball::Velocity() const {
	return velocity;
}
Vector2D Ball::setVelocity(const double x, const double y) {
	velocity.setX(x);
	velocity.setY(y);
	return velocity;
}