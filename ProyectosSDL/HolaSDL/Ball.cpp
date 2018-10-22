#include"Ball.h"
#include "Texture.h"

Ball::Ball(Vector2D position, int width, int heigth, Texture* texture, Game* game):
	position(position), width(width), heigth(heigth), velocity(), texture(texture), game(game) {};
Ball::Ball(double x, double y, int width, int heigth, Texture* texture, Game* game) :
	position(x, y), width(width), heigth(heigth), velocity(), texture(texture), game(game) {};
void Ball::render()
{
	texture->render(SDL_Rect{(int)position.getX(),(int)position.getY(),width,heigth});
};
void Ball::update() {

};